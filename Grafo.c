#include "Grafo.h"

Grafo Ini_Grafo(){
    Grafo grafo = (Grafo)malloc(sizeof(Grafo));
    grafo->No_Ini = NULL;
    grafo->V = 0;
    return grafo;
}

void Insere_No_Grafo(Grafo grafo, long int ID){
    No *no = (No*)malloc(sizeof(No));
    no->Adj = NULL;
    no->Aresta_Ini = NULL;
	no->Aresta_End = NULL;
    no->Prox = NULL;
    no->Ant = NULL;
    no->ID = ID;
    no->A = 0;
    if(grafo->V == 0){
        grafo->No_Ini = no;
        grafo->No_End = no;
    }else{
        no->Ant = grafo->No_End;
        grafo->No_End->Prox = no;
        grafo->No_End = no;
    }
    grafo->V++;
}

void Insere_Aresta_Grafo(Grafo grafo, long int ID_SRC, long int ID_DEST, int Peso){
    Aresta *aresta = (Aresta*)malloc(sizeof(Aresta));
    aresta->Ini = ID_SRC;
    aresta->Dest = ID_DEST;
    aresta->Peso = Peso;
    aresta->Prox = NULL;
    aresta->Ant = NULL;
    No* p = NULL;
    for(p = grafo->No_Ini; p->ID != ID_SRC && p != NULL; p = p->Prox) continue;
    if(p->A == 0){
        p->Adj = aresta;
        p->Aresta_Ini = aresta;
        p->Aresta_End = aresta;
    }else{
        p->Aresta_End->Prox = aresta;
        aresta->Ant = p->Aresta_End;
        p->Aresta_End = aresta;
    }
    p->A++;
}

Aresta *Busca_Aresta(Grafo grafo, long int ID_SRC, long int ID_DEST){
	No *p = NULL;
	for(p = grafo->No_Ini; p->ID != ID_SRC && p != NULL; p = p->Prox) continue;
	if(p == NULL) return NULL;
	else{
		Aresta *a = NULL;
		for(a = p->Adj; a != NULL; a = a->Prox)
			if(a->Ini == ID_SRC && a->Dest == ID_DEST) return a;
	}
	return NULL;
}

int Remove_Aresta_Grafo(Grafo grafo, long int ID_SRC, long int ID_DEST){
	Aresta *A = Busca_Aresta(grafo, ID_SRC, ID_DEST);
	No *p = NULL;
	for(p = grafo->No_Ini; p->ID != ID_SRC; p = p->Prox) continue;
	if(p->Aresta_Ini == A){
		if(p->Aresta_End == A)
			p->Aresta_End = p->Aresta_Ini->Prox;
		p->Aresta_Ini = p->Aresta_Ini->Prox;
		p->Adj = p->Aresta_Ini;
		free(A);
	}else if(p->Aresta_End == A){
		if(p->Aresta_Ini == A){
			p->Aresta_Ini = NULL;
			p->Adj = p->Aresta_Ini;
		}
		p->Aresta_End->Ant->Prox = NULL;
		p->Aresta_End = p->Aresta_End->Ant;
		free(A);
	}else{
		A->Ant->Prox = A->Prox;
		free(A);
	}
	p->A--;
	return 0;
}

int Get_Pos_No(Grafo grafo, long int ID_SRC){
	int i = 0;
	No *p = NULL;
	for(p = grafo->No_Ini; p != NULL; p = p->Prox){
		if(p->ID == ID_SRC) return i;
		i++;
	}
	return -1;
}

int BellmanFord(Grafo G, long int ID_SRC){
	int distancia[G->V];
	for(int i = 0; i < G->V; i++){
		distancia[i] = INT_MAX;
	}
	distancia[Get_Pos_No(G, ID_SRC)] = 0;
	for(No* P = G->No_Ini; P != NULL; P = P->Prox){
		for(Aresta* A = P->Aresta_Ini; A != NULL; A = A->Prox){
			if(distancia[Get_Pos_No(G, A->Ini)] + A->Peso < distancia[Get_Pos_No(G, A->Dest)]){
				distancia[Get_Pos_No(G, A->Dest)] = distancia[Get_Pos_No(G, A->Ini)] + A->Peso;
			}
		}
	}
	for(No* P = G->No_Ini; P != NULL; P = P->Prox){
		for(Aresta* A = P->Aresta_Ini; A != NULL; A = A->Prox){
			if(distancia[Get_Pos_No(G, A->Ini)] + A->Peso < distancia[Get_Pos_No(G, A->Dest)]){
				return 1;
			}
		}
	}
	return 0;
}

int Imprime_Grafo(Grafo G){
	Aresta* A;
	No* P;
	for(P = G->No_Ini; P != NULL; P = P->Prox){
		printf("%ld:", P->ID);
		for(A = P->Adj; A != NULL; A = A->Prox){
			printf(" %ld ->", A->Dest);
		}
		printf("\n");
	}
	printf("----------------------\n");
	return 0;
}

int teste(){
    Grafo G = Ini_Grafo();
    Insere_No_Grafo(G,1);
    Insere_No_Grafo(G,2);
    Insere_No_Grafo(G,3);
    Insere_No_Grafo(G,4);
    Insere_Aresta_Grafo(G, 1, 2, -1);
    Insere_Aresta_Grafo(G, 2, 3, -1);
    Insere_Aresta_Grafo(G, 3, 2, -1);
    printf("%d ", BellmanFord(G, 3));
    return 0;
}