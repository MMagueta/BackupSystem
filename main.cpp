#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <semaphore.h>
#include "Sync.h"
#include "Semaphore.h"
#include "File.h"

/*
void* sync_backup(void* args){
	struct dirent* documentos = (struct dirent*)args;
	//printf("Thread: %s\n", documentos->d_name);
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
	return NULL;
}

void sentinela(int args){
	while(1){
		printf("Sync...\n");
		
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
		
		pthread_t thread_worker[new_tam_doc];
		
		for(i = 0; i < new_tam_doc; i++){
			pthread_create(&thread_worker[i], NULL, sync_backup, new_doc[i]);
		}
		for(i = 0; i < new_tam_doc; i++){
			pthread_join(thread_worker[i], NULL);
		}
		
		sleep(2);
	}
}
*/
int main(int argc, char **argv) {

	
	//Threads
	//std::thread T(sentinela, 1);
	//T.join();
	
	File f("./documentos/teste.txt");
	std::cout << f.Blocks[2][1] << std::endl;
	
	printf("---------------------\n");

	return 0;
}
