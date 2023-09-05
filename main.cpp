#include <iostream>
#include "thread_pool.h"

class ExampleApp_t : public IRunnable_t
{
    public:
        std::shared_ptr<IRunnable_t> next;
        std::string note;
    public:
        ExampleApp_t()
        {
            next = nullptr;
            note = "hello";
        }
        ExampleApp_t(const std::string &n)
        {
            next = nullptr;
            note = n;
        }
        virtual ~ExampleApp_t()
        {
        }

        virtual void Run(void)
        {
            std::cout << __FUNCTION__ << "  " << note << std::endl;
        }

        virtual std::shared_ptr<IRunnable_t>& Next(void)
        {
            return next;
        }

        virtual void Next(std::shared_ptr<IRunnable_t>& val)
        {
            next = val;
        }
};

int main()
{
    std::shared_ptr<ThreadPool_t> threadPool = std::make_shared<ThreadPool_t>();
    int status = threadPool->Initialise(5);
    if (0 == status) {
        std::cout << "threadPool init ok" << std::endl;
    }

    {
        std::shared_ptr<IRunnable_t> runnableObject = std::make_shared<ExampleApp_t>();
        threadPool->QueueToThreadPool(runnableObject);
    }

    {
        std::shared_ptr<IRunnable_t> runnableObject = std::make_shared<ExampleApp_t>("world");
        threadPool->QueueToThreadPool(runnableObject);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    threadPool->Shutdown();
    
    return 0;
}