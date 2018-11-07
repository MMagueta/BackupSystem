//Link: https://stackoverflow.com/questions/24465533/implementing-boostbarrier-in-c11

#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>

class Barrier {
public:
    explicit Barrier(std::size_t count) : _count(count) { };
    void Wait();
private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::size_t _count;
};

#endif /* BARRIER_H */