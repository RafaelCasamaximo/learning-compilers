// #ifndef __GRAPH_H_
// #define __GRAPH_H_

// typedef struct edge
// {
//     // Representa a referencia das outras arestas na lista do vertice.
//     struct edge* previous;
//     struct edge* next;
//     // Qual o destino da aresta
//     int vertexId;
// }Edge;

// typedef struct vertex
// {
//     // Representa a referencia dos outros vertices na lista do grafo.
//     struct vertex* previous;
//     struct vertex* next;
//     // Um vertice como um elemento com uma lista encadeada de arestas que partem dele
//     Edge* first;
//     Edge* last;
//     // Informações necessárias para o algoritmo
//     int id;
//     int degree;
//     int color;
// }Vertex;

// typedef struct graph
// {
//     // Grafo como uma lista encadeada de vertices
//     Vertex* first;
//     Vertex* last;
//     // Salva o número de vertices do grafo
//     int vertexNumber;
// }Graph;

// /*
//     Aloca um novo grafo
// */
// Graph* createGraph();

// /*
//     Aloca um novo vertice
// */
// Vertex* createVertex(int vertexId);

// /*
//     Insere um novo vertice num grafo
// */
// void insertVertexGraph(Graph* graph, Vertex* vertex);

// /*
//     Insere uma nova aresta em um vertice e define o destino para o id indicado.
//     Não checa se o destino da aresta existe.
// */
// void insertEdgeVertexGraph(Vertex* sourceVertex, int destinyVertexId);

// /*
//     Insere uma aresta a partir de um ID inicial e de um ID final.
// */
// void insertEdgeGraph(Graph* graph, int sourceVertexId, int destinyVertexId);

// /*
//     Remove uma aresta a partir de um vertice inicial e de um ID final.
// */
// void removeEdgeGraph(Vertex* vertex, int destinyVertexId);

// /*
//     Remove um vertice do grafo e suas arestas.
// */
// void removeVertexGraph(Graph* graph, Vertex* vertex);

// /*
//     Remove todos os vertices e arestas do grafo. Desaloca o grafo ao final.
// */
// void deleteGraph(Graph* graph);

// #endif

#ifndef __GRAPH_H_
#define __GRAPH_H_

typedef struct ArestaStruct{
    int vertexId;
    struct ArestaStruct *next;
    struct ArestaStruct *previous;
}Edge;

typedef struct VerticeStruct{
    struct VerticeStruct* next;
    struct VerticeStruct* previous;
    Edge *first;
    Edge *last;
    int degree;
    int color;
    int id;
}Vertex;

typedef struct GrafoStruct{
    Vertex *first;
    Vertex *last;
    int vertexNumber;
}Grafo;


Grafo *createGraph();

Vertex* createVertex(int id);

int insertVertexGraph(Vertex* vertexId, Grafo *grafo);

int addArestaVertice(Vertex* v1, int v2);

int addArestaGrafo(int v1, int v2, Grafo *grafo);

int removeVertice(Grafo *Grafo, Vertex *vertexId);

void removeGrafo(Grafo *Grafo);

#endif