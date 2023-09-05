#include <iostream>
#include "thread_pool.h"

void ThreadPool_t::MessagePump(void)
{
    runningThreads.Increment();
    std::cout << "thread " << std::this_thread::get_id() << " enter" << std::endl;
    while(!quit.Value()) {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [this] { return quit.Value() || !runQueue->IsEmpty(); });
        lk.unlock();

        std::cout << "thread " << std::this_thread::get_id() << " wake" << std::endl;

        std::shared_ptr<IRunnable_t> job;
        if (runQueue) {
            runQueue->Pop(job);
            while(job && !quit.Value()) {
                job->Run();
                runQueue->Pop(job);
            }
        }
    }
    std::cout << "thread " << std::this_thread::get_id() << " exit" << std::endl;

    runningThreads.Decrement();
}

void ThreadPool_t::Cleanup(void)
{
    if (!threads.empty()) {
        {
            std::lock_guard<std::mutex> lk(mtx);
            quit.Value(true);
        }
        std::cout << "notify condition " << std::endl;
        cv.notify_all();
        for (auto& t : threads) {
            t.join();
        }
        threads.clear();
    }

    running = false;
}


ThreadPool_t::ThreadPool_t() : running(false)
{
}

ThreadPool_t::~ThreadPool_t()
{
    Cleanup();
}

int ThreadPool_t::Initialise(uint32_t noOfThreads)
{
    int status;
    runQueue = std::make_shared<SafeIntrusiveEmbeddedQueue_t<IRunnable_t>>();
    if (!runQueue) {
        std::cout << "Create runQueue failed" << std::endl;
        return -1;
    }
    status = runQueue->Initialise();
    if (status) {
        std::cout << "Init failed" << std::endl;
        return status;
    }

    status = quit.Initialise();
    status = runningThreads.Initialise();

    for (uint32_t i = 0; i < noOfThreads; i++) {
        threads.push_back(std::thread(&ThreadPool_t::MessagePump, this));
    }

    while((uint32_t)(runningThreads.Value()) < noOfThreads) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    running = true;

    return 0;
}

int ThreadPool_t::QueueToThreadPool(std::shared_ptr<IRunnable_t>& objectToRun)
{
    if (running && runQueue) {
        {
            std::lock_guard<std::mutex> lk(mtx);
            runQueue->Push(objectToRun);
            std::cout << "queue count: " << runQueue->Count() << std::endl;
        }
        cv.notify_one();
    }
    return 0;
}

int ThreadPool_t::Operate(void)
{
    //nothing to do now
    return -1;
}

int ThreadPool_t::Shutdown(void)
{
    Cleanup();

    return 0;
}

