#include "Sync.h"

void Sync::Updater(char* cur, char* bkp){
	struct stat path_stat;
	stat(cur, &path_stat);

	struct stat bkp_stat;
	stat(bkp, &bkp_stat);
	
	char buff1[BLOCO];
	char buff2[BLOCO];
	
	int fd1 = open(cur, O_RDONLY);
	int fd2 = open(bkp, O_WRONLY);
	
	int div = path_stat.st_size / BLOCO;
	
	int i, n;
	
	ssize_t w1, r1, w2, r2;
	size_t size1, size2;
	
	n = 0;
	
	for(i=0;i<=div;i++){
	
		r1 = read(fd1,buff1,BLOCO);
		r2 = read(fd2,buff2,BLOCO);
		
		if(strcmp(buff1,buff2)!=0){
			size1 = (size_t)r1;
			size2 = (size_t)r2;
			
			if(strcmp(buff1,buff2) != 0){
				
				w1 = write(fd2,buff1,size1);
			
				n = n+BLOCO;
				lseek(fd1,n,SEEK_SET);
				lseek(fd2,n,SEEK_SET);
				
				w2 = ftruncate(fd2,path_stat.st_size);
			
				bzero(buff1, BLOCO);
				bzero(buff2, BLOCO);	
			}
		}
	}
}

