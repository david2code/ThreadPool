#pragma once
#include "intrusive_embedded_queue_t.h"
#include "auto_lock_t.h"

template<class T>
class SafeIntrusiveEmbeddedQueue_t
{
    private:
        IntrusiveEmbeddedQueue_t<T> queue;
        Lock_t lock;
    public:
        int Initialise(void)
        {
            return lock.Initialise();
        }

        void Push(std::shared_ptr<T>& item)
        {
            AutoLock_t lk(lock);
            queue.Push(item);
        }

        void Push(std::shared_ptr<T>& item, uint32_t& count_)
        {
            AutoLock_t lk(lock);
            queue.Push(item);
            count_ = queue.Count();
        }

        void Pop(std::shared_ptr<T>& item)
        {
            AutoLock_t lk(lock);
            queue.Pop(item);
        }

        void Pop(std::shared_ptr<T>& item, uint32_t& count_)
        {
            AutoLock_t lk(lock);
            queue.Pop(item);
            count_ = queue.Count();
        }

        uint32_t Count(void)
        {
            AutoLock_t lk(lock);
            return queue.Count();
        }

        bool IsEmpty(void)
        {
            AutoLock_t lk(lock);
            return (queue.Count() == 0);
        }

};
