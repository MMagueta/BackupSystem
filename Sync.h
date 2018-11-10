#ifndef SYNC_H
#define SYNC_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <fcntl.h>
#include "Sync.h"
#include "File.h"
#include <semaphore.h>

#define BLOCO 512



class Sync {
public:
<<<<<<< HEAD
    Sync(sem_t*, sem_t*);
=======
    Sync(sem_t*);
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
    void Updater(char*, char*);
    void Sentinel();
    void Syncronize(struct dirent*);
    int Curling(std::string, char*);
<<<<<<< HEAD
    sem_t* sem_buff1;
    sem_t* sem_buff2;
=======
    sem_t* semaforo;
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
    Sync* sync_ptr;
    
private:
    std::vector<File> Documents;
    char buff1[BLOCO];
    char buff2[BLOCO];

};

#endif /* SYNC_H */