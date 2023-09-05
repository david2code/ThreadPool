#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "atomic_t.h"
#include "safe_intrusive_embedded_queue_t.h"
#include "irunnable_t.h"

class ThreadPool_t
{
    private:
        std::mutex mtx;
        std::condition_variable cv;
        std::shared_ptr<SafeIntrusiveEmbeddedQueue_t<IRunnable_t>> runQueue;
        Atomic_t<bool> quit;
        Atomic_t<uint32_t> runningThreads;
        std::vector<std::thread> threads;
        bool running;

        void MessagePump(void);
        void Cleanup(void);
    public:
        ThreadPool_t();
        ~ThreadPool_t();

        int Initialise(uint32_t noOfThreads);
        virtual int QueueToThreadPool(std::shared_ptr<IRunnable_t>& objectTorun);
        virtual int Operate(void);
        int Shutdown(void);
};
