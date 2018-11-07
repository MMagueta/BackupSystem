//Link: https://stackoverflow.com/questions/24465533/implementing-boostbarrier-in-c11

#include "Barrier.h"

void Barrier::Wait(){
    std::unique_lock<std::mutex> lock(this->_mutex);
    if(--this->_count == 0){
        this->_cv.notify_all();
    }else{
        this->_cv.wait(lock, [this] { return this->_count == 0; });
    }
}