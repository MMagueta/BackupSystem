#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct S_Aresta{
    long int Ini;
    long int Dest;
    int Peso;
    struct S_Aresta *Prox;
    struct S_Aresta *Ant;
} Aresta;

typedef struct S_No{
    struct S_Aresta *Adj;
    struct S_Aresta *Aresta_Ini;
    struct S_Aresta *Aresta_End;
    struct S_No *Prox;
    struct S_No *Ant;
    int A;
    long int ID;
} No;

typedef struct S_Graph{
    int V;
    No *No_Ini;
    No *No_End;
} *Grafo;

Grafo Ini_Grafo();

void Insere_No_Grafo(Grafo, long int);

void Insere_Aresta_Grafo(Grafo, long int, long int, int);

Aresta *Busca_Aresta(Grafo, long int, long int);

int Remove_Aresta_Grafo(Grafo, long int, long int);

int Get_Pos_No(Grafo, long int);

int BellmanFord(Grafo, long int);

int Imprime_Grafo(Grafo);

#endif /* GRAFO_H */

