#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore (int count_ = 0)
        : count(count_) {}
    void Notify();
    void Wait();
};

#endif /* SEMAPHORE_H */