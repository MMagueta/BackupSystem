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
	
<<<<<<< HEAD
	sem_t sem_buff1;
	sem_t sem_buff2;
	
	Sync s_ptr(&sem_buff1, &sem_buff2);
	sem_init(s_ptr.sem_buff1, 0, 1);
=======
	sem_t semaforo;
	
	Sync s_ptr(&semaforo);
	sem_init(s_ptr.semaforo, 0, 1);
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
	s_ptr.sync_ptr = &s_ptr;
	std::thread T(&Sync::Sentinel, &s_ptr);
	T.join();
	delete &s_ptr;
	
	printf("---------------------\n");

	return 0;
}
