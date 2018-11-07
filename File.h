#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>
#include <iostream>
#include <sys/stat.h>
#define BLOCO 512

class File {
public:
    File(std::string);
private:
    std::vector<std::vector<int>> Blocks;
    std::vector<bool> Flags;
    std::string Path;
    struct stat Stat;

    
};

#endif /* FILE_H */

