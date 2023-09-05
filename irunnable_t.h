#pragma once

class IRunnable_t
{
    public:
        virtual ~IRunnable_t() {}

        virtual std::shared_ptr<IRunnable_t>& Next(void) = 0;
        virtual void Next(std::shared_ptr<IRunnable_t>& val) = 0;
        virtual void Run(void) = 0;
};


