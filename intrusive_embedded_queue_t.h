#pragma once

template<class T>
class IntrusiveEmbeddedQueue_t
{
    private:
        std::shared_ptr<T> first;
        std::shared_ptr<T> last;
        uint32_t count;
    public:
        IntrusiveEmbeddedQueue_t() : first(0), last(0), count(0U)
        {
        }
        ~IntrusiveEmbeddedQueue_t()
        {
        }

        void Push(std::shared_ptr<T>& item)
        {
            if (item) {
                item->Next() = nullptr;
                if (!first) {
                    first = item;
                    last =  item;
                    count = 1U;
                }
                else if (last) {
                    last->Next(item);
                    last = last->Next();
                    count++;
                }
            }
        }

        void Pop(std::shared_ptr<T>& item)
        {
            if (first) {
                item = first;
                first = first->Next();
                item->Next() = nullptr;
                if (--count == 0U) {
                    last = nullptr;
                }
            } else {
                item = nullptr;
            }
        }

        uint32_t Count(void) const
        {
            return count;
        }

};
