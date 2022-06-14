#ifndef __customGraph__
#define __customGraph__



typedef struct ArestaStruct{
    int vertice;
    struct ArestaStruct *prox;
    struct ArestaStruct *ant;
}Aresta;

typedef struct VerticeStruct{
    struct VerticeStruct* prox;
    struct VerticeStruct* ant;
    Aresta *primeiro;
    Aresta *ultimo;
    int grau;
    int cor;
    int id;
}Vertice;

typedef struct GrafoStruct{
    Vertice *primeiro;
    Vertice *ultimo;
    int tamanho;
}Grafo;


Grafo *criarGrafo();

Vertice* criarVertice(int id);

int addVertice(Vertice* vertice, Grafo *grafo);

int addArestaVertice(Vertice* v1, int v2);

int addArestaGrafo(int v1, int v2, Grafo *grafo);

int removeVertice(Grafo *Grafo, Vertice *vertice);

void removeGrafo(Grafo *Grafo);

#endif