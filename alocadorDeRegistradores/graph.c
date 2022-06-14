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
