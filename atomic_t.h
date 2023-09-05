#pragma once

#include <atomic>
template<class T>
class Atomic_t
{
    private:
        std::atomic<T> value;
    public:
        Atomic_t() : value(T())
        {
        }

        int Initialise(void)
        {
            return 0;
        }

        T Value(void) const
        {
            return value;
        }

        void Value(T val)
        {
            value = val;
        }

        T Increment(void)
        {
            return value.fetch_add(1);
        }

        T Decrement(void)
        {
            return value.fetch_sub(1);
        }
};
