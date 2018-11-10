#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <semaphore.h>
#include "Sync.h"
#include "File.h"

int main(int argc, char **argv) {
	
	//File f("./documentos/teste.txt");
	//std::cout << f.Blocks[2][1] << std::endl;
	
	sem_t sem_buff1;
	sem_t sem_buff2;
	
	Sync s_ptr(&sem_buff1, &sem_buff2);
	sem_init(s_ptr.sem_buff1, 0, 1);
	s_ptr.sync_ptr = &s_ptr;
	std::thread T(&Sync::Sentinel, &s_ptr);
	T.join();
	delete &s_ptr;
	
	printf("---------------------\n");

	return 0;
}
