#pragma once

#include <mutex>

class Lock_t
{
    private:
        std::recursive_mutex mtx;
    public:
        int Initialise(void)
        {
            return 0;
        }


        void Enter(void)
        {
            mtx.lock();
        }
        void Exit(void)
        {
            mtx.unlock();
        }
};
