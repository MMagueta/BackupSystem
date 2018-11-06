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

#define BLOCO 512

class Sync {
public:
    Sync();
    void Updater(char*, char*);
    void Sentinel();
    void Syncronize(struct dirent*);
private:
    std::vector<File> Documents;

};

#endif /* SYNC_H */