#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"



Grafo *criarGrafo() {
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->primeiro = NULL;
    grafo->ultimo = NULL;
    grafo->tamanho = 0;
    return grafo;
}

Vertice* criarVertice(int id){
    Vertice* vertice = malloc(sizeof(Vertice));
    vertice->primeiro = NULL;
    vertice->ultimo = NULL;
    vertice->id = id;
    vertice->grau = 0;
    vertice->cor = -1;
    return vertice;
}

int addArestaVertice(Vertice* v1, int v2){
    if(v1 == NULL){
        return 0;
    }

    Aresta *a;
    for(a = v1->primeiro; a != NULL; a = a->prox){
        if(a->vertice == v2){
            return 0;
        }
    }

    Aresta* aresta = malloc(sizeof(Aresta));
    aresta->vertice = v2;

    if(v1->primeiro == NULL) {
        aresta->ant = NULL;
        v1->primeiro = aresta;
    } else {
        v1->ultimo->prox = aresta;
        aresta->ant = v1->ultimo;
    }
    aresta->prox = NULL;
    v1->ultimo = aresta;
    v1->grau++;
    return 1;
}

int addVertice(Vertice* vertice, Grafo *grafo){
    if(grafo == NULL || vertice == NULL){
        return 0;
    }
    Vertice *v;
    for(v = grafo->primeiro; v != NULL; v = v->prox){
        Aresta *a;
        for(a = vertice->primeiro; a != NULL; a = a->prox){
            if (v->id == a->vertice){
                addArestaVertice(v, vertice->id);
            }
        }
        for(a = v->primeiro; a != NULL; a = a->prox){
            if (vertice->id == a->vertice){
                addArestaVertice(vertice, v->id);
            }
        }     
    }
    if(grafo->primeiro == NULL) {
        vertice->ant = NULL;
        grafo->primeiro = vertice;
    } else {
        grafo->ultimo->prox = vertice;
        vertice->ant = grafo->ultimo;
    }
    vertice->prox = NULL;
    grafo->ultimo = vertice;
    grafo->tamanho++;
    return 1;
}

int addArestaGrafo(int id1, int id2, Grafo *grafo){
    if(grafo == NULL){
        return 0;
    }
    Vertice *v;
    for(v = grafo->primeiro; v != NULL; v = v->prox){
        if (v->id == id1){
            addArestaVertice(v, id1);
        }
        else if(v->id == id2){
            addArestaVertice(v, id2);
        }
    }
    return 1;
}

int removeAresta(Vertice * vertice, int id){
    if(vertice == NULL){
        return 0;
    }
    Aresta *a, *aresta = NULL;
    for(a = vertice->primeiro; a != NULL; a = a->prox){
        if(a->vertice == id){
            aresta = a;
            break;
        }
    }
    if (aresta == NULL){
        return 0;
    }
    if(aresta->ant == NULL){
        vertice->primeiro = aresta->prox;
    }else{
        aresta->ant->prox = aresta->prox;
    }
    if(aresta->prox == NULL){
        vertice->ultimo = aresta->ant;
    }else{
        aresta->prox->ant = aresta->ant;
    }
    vertice->grau--;
    free(aresta);
    return 1;
}

int removeVertice(Grafo *grafo, Vertice *vertice){
    if(grafo == NULL || vertice == NULL){
        return 0;
    }
    Vertice *v;
    for(v = grafo->primeiro; v != NULL; v = v->prox){
        removeAresta(v, vertice->id);
    }
    if(vertice->ant == NULL){
        grafo->primeiro = vertice->prox;
    }else{
        vertice->ant->prox = vertice->prox;
    }
    if(vertice->prox == NULL){
        grafo->ultimo = vertice->ant;
    }else{
        vertice->prox->ant = vertice->ant;
    }
    grafo->tamanho--;
    
    return 1;
}

void removeGrafo(Grafo *grafo){
    if(grafo == NULL){
        return;
    }
    Vertice* v = grafo->primeiro;
    while (v != NULL){
        Aresta* a = v->primeiro;
        while (a != NULL){

            Aresta* antA = a;
            a = a->prox;
            free(antA);
        }
        Vertice* antV = v;
        v = v->prox;
        free(antV);
    }
    free(grafo);
}