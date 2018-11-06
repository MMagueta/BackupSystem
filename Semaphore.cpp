//Font: https://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
#include "Semaphore.h"

void Semaphore::Notify(){ //SemPost
	std::unique_lock<std::mutex> lock(this->mtx);
	this->count++;
	this->cv.notify_one();
}

void Semaphore::Wait(){ //SemWait
	std::unique_lock<std::mutex> lock(this->mtx);
	while(this->count == 0){
		this->cv.wait(lock);
	}
	this->count--;
}