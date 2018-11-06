#include "File.h"

File::File(std::string path){
	stat(path.c_str() , &this->Stat);
	int div = this->Stat.st_size/BLOCO;
	int block_1 = 0;
	int block_2 = BLOCO;
	for(int i = 0; i <= div; i++){
		this->Blocks.push_back(std::vector<int>{block_1, block_2});
		block_1 += BLOCO;
		block_2 += BLOCO;
	}
    this->Path = path;
    
}
