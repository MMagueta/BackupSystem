#include "Sync.h"
#include <iostream>

Sync::Sync(){
	
}

void Sync::Syncronize(struct dirent* documentos){
	Sync obj;
	struct stat buffer_doc, buffer_bak;
	if(documentos->d_type == DT_REG){
		char string[250];
		char string2[250];
		sprintf(string, "./backup/%s", documentos->d_name);
		sprintf(string2, "./documentos/%s", documentos->d_name);
		stat(string, &buffer_bak);
		stat(string2, &buffer_doc);
		if(open(string, O_RDONLY) == -1){
			open(string, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			obj.Updater(string2, string);
			printf("Sincronizado: %s\n", string);
		}else if(buffer_doc.st_mtime > buffer_bak.st_mtime){
			obj.Updater(string2, string);
			printf("Sincronizado: %s\n", string);
		}
	}
}

void Sync::Sentinel(){
	while(1){
		std::cout << "Sync..." << std::endl;
		
		struct dirent **doc;
		struct dirent **new_doc;
	
		int tam_doc = scandir("./documentos/", &doc, NULL, alphasort);
		struct stat *documentos = (struct stat*)malloc(tam_doc*sizeof(struct stat));

		int i = 0;
		int new_tam_doc = 0;
		while(i < tam_doc){
			if(doc[i]->d_type == DT_REG){
				char string[250];
				sprintf(string, "./documentos/%s", doc[i]->d_name);
				stat(string, &documentos[new_tam_doc]);
				new_tam_doc++;
			}
			i++;
		}
		new_doc = (struct dirent **)malloc(new_tam_doc*sizeof(struct dirent*));
		
		struct dirent **bak;
		struct dirent **new_bak;
		
		int	tam_bak = scandir("./backup/", &bak, NULL, alphasort);
		struct stat *backup = (struct stat*)malloc(tam_bak*sizeof(struct stat));

		i = 0;
		int new_tam_bak = 1;
		while(i < tam_bak){
			if(bak[i]->d_type == DT_REG){
				char string[250];
				sprintf(string, "./backup/%s", bak[i]->d_name);
				stat(string, &backup[new_tam_bak-1]);
				new_tam_bak++;
			}
			i++;
		}
		new_doc = (struct dirent **)malloc(new_tam_doc*sizeof(struct dirent*));
		
		int j = 0;
		for(i = 0; i < tam_doc; i++){
			if(doc[i]->d_type == DT_REG){
				new_doc[j] = doc[i];
				j++;
			}
		}
		
		std::vector<std::thread> T;
		Sync *sync_ptr;
		
		for(i = 0; i < new_tam_doc; i++){
			T.push_back(std::thread(&Sync::Syncronize, sync_ptr, new_doc[i]));
		}
		for(i = 0; i < new_tam_doc; i++){
			T[i].join();
		}
		
		sleep(2);
	}
}

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

