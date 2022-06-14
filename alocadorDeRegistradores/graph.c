// #include <stdio.h>
// #include <stdlib.h>
// #include "graph.h"

// Graph* createGraph()
// {
//     Graph* graph = malloc(sizeof(Graph));

//     graph->first = NULL;
//     graph->last = NULL;
//     graph->vertexNumber = 0;

//     return graph;
// }

// Vertex* createVertex(int vertexId)
// {
//     Vertex* vertex = malloc(sizeof(Vertex));

//     vertex->first = NULL;
//     vertex->last = NULL;

//     vertex->id = vertexId;
//     vertex->degree = 0;
//     vertex->color = -1;

//     return vertex;
// }

// void insertVertexGraph(Graph* graph, Vertex* vertex)
// {
//     // Completa o grafo caso esteja incompleto
//     // Insere uma edge de cada lado do vertice que tiver faltando
//     for(Vertex* auxVertex = graph->first; auxVertex != NULL; auxVertex = auxVertex->next)
//     {
//         for(Edge* auxEdge = vertex->first; auxEdge != NULL; auxEdge = auxEdge->next)
//         {
//             if(auxVertex->id == auxEdge->vertexId)
//             {
//                 insertEdgeVertexGraph(auxVertex, vertex->id);
//             }
//         }
//         for(Edge* auxEdge = auxVertex->first; auxEdge != NULL; auxEdge = auxEdge->next)
//         {
//             if(vertex->id == auxEdge->vertexId)
//             {
//                 insertEdgeVertexGraph(vertex, auxVertex->id);
//             }
//         }
//     }

//     // Caso seja o primeiro do grafo
//     if(graph->first == NULL)
//     {
//         vertex->previous = NULL;
//         graph->first = vertex;
//     }
//     // Caso não seja o primeiro, atualiza o último
//     else
//     {
//         graph->last->next = vertex;
//         vertex->previous = graph->last;
//     }

//     vertex->next = NULL;
//     graph->last = vertex;
//     graph->vertexNumber++;
// }

// void insertEdgeVertexGraph(Vertex* sourceVertex, int destinyVertexId)
// {
//     // Procura se já existe
//     for(Edge* auxEdge = sourceVertex->first; auxEdge != NULL; auxEdge = auxEdge->next){
//         if(auxEdge->vertexId == destinyVertexId){
//             return;
//         }
//     }

//     Edge* auxEdge = malloc(sizeof(Edge));
//     auxEdge->vertexId = destinyVertexId;

//     // Primeira aresta
//     if(sourceVertex->first == NULL)
//     {
//         auxEdge->previous = NULL;
//         sourceVertex->first = auxEdge;
//     }
//     else
//     {
//         sourceVertex->last->next = auxEdge;
//         auxEdge->previous = sourceVertex->last;
//     }

//     auxEdge->next = NULL;
//     sourceVertex->last = auxEdge;
//     sourceVertex->degree++;
// }

// void insertEdgeGraph(Graph* graph, int sourceVertexId, int destinyVertexId)
// {
//     for(Vertex* auxVertex = graph->first; auxVertex != NULL; auxVertex = auxVertex->next)
//     {
//         if(auxVertex->id == sourceVertexId)
//         {
//             insertEdgeVertexGraph(auxVertex, sourceVertexId);
//         }
//         else if(auxVertex->id == destinyVertexId)
//         {
//             insertEdgeVertexGraph(auxVertex, destinyVertexId);
//         }
//     }
// }

// void removeEdgeGraph(Vertex* vertex, int destinyVertexId)
// {
//     Edge* auxRemovedEdge = NULL;

//     for(Edge* auxEdge = vertex->first; auxEdge != NULL; auxEdge = auxEdge->next)
//     {
//         if(auxEdge->vertexId == destinyVertexId)
//         {
//             auxRemovedEdge = auxEdge;
//             break;
//         }
//     }

//     if(auxRemovedEdge == NULL)
//     {
//         return;
//     }

//     if(auxRemovedEdge->previous == NULL)
//     {
//         vertex->first = auxRemovedEdge->next;
//     }
//     else
//     {
//         auxRemovedEdge->previous->next = auxRemovedEdge->next;
//     }

//     if(auxRemovedEdge->next == NULL)
//     {
//         vertex->last = auxRemovedEdge->previous;
//     }
//     else
//     {
//         auxRemovedEdge->next->previous = auxRemovedEdge->previous;
//     }

//     vertex->degree--;
    
//     free(auxRemovedEdge);
// }

// void removeVertexGraph(Graph* graph, Vertex* vertex)
// {
//     for(Vertex* auxVertex = graph->first; auxVertex != NULL; auxVertex = auxVertex->next)
//     {
//         removeEdgeGraph(auxVertex, vertex->id);
//     }

//     if(vertex->previous == NULL)
//     {
//         graph->first = vertex->next;
//     }
//     else
//     {
//         vertex->previous->next = vertex->next;
//     }

//     if(vertex->next == NULL)
//     {
//         graph->last = vertex->previous;
//     }
//     else
//     {
//         vertex->next->previous = vertex->previous;
//     }

//     graph->vertexNumber--;
// }

// void deleteGraph(Graph* graph)
// {
//     Vertex* auxVertex = graph->first;

//     while(auxVertex != NULL)
//     {
//         Edge* auxEdge = auxVertex->first;
        
//         while(auxEdge != NULL)
//         {
//             Edge* previousAuxEdge = auxEdge;
//             auxEdge = auxEdge->next;
//             free(previousAuxEdge);
//         }

//         Vertex* previousAuxVertex = auxVertex;
//         auxVertex = auxVertex->next;
//         free(previousAuxVertex);
//     }
//     free(graph);
// }


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