#pragma once
#include "lock_t.h"

class AutoLock_t
{
    private:
        Lock_t& lock;
    public:
        AutoLock_t(Lock_t& lock_) : lock(lock_)
        {
            lock.Enter();
        }
        ~AutoLock_t()
        {
            lock.Exit();
        }
};
