#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#include "Grafo.h"

int (* _sem_wait)(sem_t *) = NULL;
int (* _sem_post)(sem_t *) = NULL;
int (* _sem_init)(sem_t *, int, unsigned int) = NULL;
int (* _sem_getvalue)(sem_t *, int *) = NULL;

Grafo G;
int num_semaforos = 0;

int sem_init(sem_t *sem, int pshared, unsigned int value){
	int R;
	if(!_sem_init){
		_sem_init = dlsym(RTLD_NEXT, "sem_init");
	}
	
	if(num_semaforos == 0){ //Inicia o grafo no primeiro semaforo iniciado
		G = Ini_Grafo();
	}
		
	num_semaforos++;

	R = _sem_init(sem, pshared, value);
	return R;
}

int sem_getvalue(sem_t *sem, int* sval){
	if(!_sem_getvalue){
		_sem_getvalue = dlsym(RTLD_NEXT, "sem_getvalue");
	}
	
	int R = _sem_getvalue(sem, sval);
	return R;
}

int sem_wait(sem_t *sem){
	if(!_sem_wait){
		_sem_wait = dlsym(RTLD_NEXT, "sem_wait");
	}
	long int id_recurso = (intptr_t)sem;
	if(Get_Pos_No(G, (intptr_t)sem) == -1){
		Insere_No_Grafo(G, (intptr_t)sem);
	}
	if(Get_Pos_No(G, pthread_self()) == -1){
		Insere_No_Grafo(G, pthread_self());
	}
	
	Insere_Aresta_Grafo(G, pthread_self(), (intptr_t)sem, -1); //Insere a aresta de requisicao
	
	printf("Ciclo: %d\n", BellmanFord(G, (intptr_t)sem));
	Imprime_Grafo(G);
	if(!BellmanFord(G, (intptr_t)sem)){
		Remove_Aresta_Grafo(G, pthread_self(), (intptr_t)sem); //Remove a aresta de requisicao
		Insere_Aresta_Grafo(G, (intptr_t)sem, pthread_self(), -1); //Insere a aresta de alocacao
		return _sem_wait(sem);
	}else{
		Remove_Aresta_Grafo(G, pthread_self(), (intptr_t)sem); //Remove a aresta de requisicao
		return -1;
	}
}


int sem_post(sem_t *sem){
	int R;
	if(!_sem_post){
		_sem_post = dlsym(RTLD_NEXT, "sem_post");
	}
	
	Aresta *A = Busca_Aresta(G, (intptr_t)sem, pthread_self());
	if(A)
		Remove_Aresta_Grafo(G, (intptr_t)sem, pthread_self());

	R = _sem_post(sem);
	return R;
}
