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
    Sync(sem_t*);
    void Updater(char*, char*);
    void Sentinel();
    void Syncronize(struct dirent*);
    int Curling(std::string, char*);
    sem_t* semaforo;
    Sync* sync_ptr;
    
private:
    std::vector<File> Documents;
    char buff1[BLOCO];
    char buff2[BLOCO];

};

#endif /* SYNC_H */