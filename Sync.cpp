#include "Sync.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

char buff1[BLOCO];
char buff2[BLOCO];

<<<<<<< HEAD
Sync::Sync(sem_t* sem_buff1, sem_t* sem_buff2){
	this->sem_buff1 = sem_buff1;
	this->sem_buff2 = sem_buff2;
=======
Sync::Sync(sem_t* semaforo){
	this->semaforo = semaforo;
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
}

int Sync::Curling(std::string url, char* data){
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    /* Now specify the POST data */ 
	std::string str("data=" + std::string(data));
	std::cout << str << std::endl;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str.c_str());

    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}

void Sync::Syncronize(struct dirent* documentos){

	struct stat buffer_doc, buffer_bak;
	if(documentos->d_type == DT_REG){
		char string[250];
		char string2[250];
		sprintf(string, "./backup/%s", documentos->d_name);
		sprintf(string2, "./documentos/%s", documentos->d_name);
		stat(string, &buffer_bak);
		stat(string2, &buffer_doc);
		if(open(string, O_RDONLY) == -1){//Se o arquivo nao existe
			open(string, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			this->Updater(string2, string);
			printf("Sincronizado: %s\n", string);
		}else if(buffer_doc.st_mtime > buffer_bak.st_mtime){
			this->Updater(string2, string);
			printf("Sincronizado: %s\n", string);
		}
	}
}

void Sync::Sentinel(){
	while(true){
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
<<<<<<< HEAD
		Sync sync_ptr(this->sem_buff1, this->sem_buff2);
=======
		Sync sync_ptr(this->semaforo);
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
		
		for(i = 0; i < new_tam_doc; i++){
			T.push_back(std::thread(&Sync::Syncronize, &sync_ptr, new_doc[i]));
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
	
	
	
	int fd1 = open(cur, O_RDONLY);
	int fd2 = open(bkp, O_WRONLY);
	
	int div = path_stat.st_size / BLOCO;
	
	int i, n;
	
	ssize_t w1, r1, w2, r2;
	size_t size1, size2;
	
	n = 0;
	
	for(i = 0; i <= div; i++){
		
<<<<<<< HEAD
		sem_wait(this->sem_buff1);
		r1 = read(fd1,buff1,BLOCO);
		sem_wait(this->sem_buff2);
=======
		sem_wait(this->semaforo);
		
		r1 = read(fd1,buff1,BLOCO);
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
		r2 = read(fd2,buff2,BLOCO);
		
		//
		
		//this->Curling("http://localhost:8000/store/", buff1);
		
		//
		
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
<<<<<<< HEAD
		sem_post(this->sem_buff1);
		sem_post(this->sem_buff2);
=======
		sem_post(this->semaforo);
>>>>>>> 5434c105665a869e013ca9e8696b0d2b1c67be5f
	}
	
	
}

