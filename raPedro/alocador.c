#include "alocador.h"
#include <string.h>
#include <stdlib.h>

Grafo* build(FILE* file){
    Grafo* grafo = criarGrafo();
    int nVertice;
    while(fscanf(file, "%d -->", &nVertice) != EOF){
        Vertice* vertice = criarVertice(nVertice);
        char c = fgetc(file);
        while(c == ' '){
            int nAresta;
            fscanf(file, "%d", &nAresta);
            addArestaVertice(vertice, nAresta);
            c = fgetc(file);
        }
        addVertice(vertice, grafo);
    }
    return grafo;
}

Stack* simplify(Grafo* graph, int k){

    Stack* pilha = stackCreate();

    int n = graph->tamanho;
    int i;
    for(i = 0; i < n; i++){

        Vertice *v, *vmin = NULL, *vmax = NULL;
        int min = 0, max = 0;
        
        for(v = graph->primeiro; v != NULL; v = v->prox){
            int nArestas = v->grau;
            if(vmin == NULL || nArestas < min){
                vmin = v;
                min = nArestas;
            }
            else if(nArestas == min){
                if (vmin->id > v->id){
                    vmin = v;
                }
            }
            if(vmax == NULL || nArestas > max){
                vmax = v;
                max = nArestas;
            }
            else if(nArestas == max){
                if (vmax->id > v->id){
                    vmax = v;
                }
            }
        }
        if (min < k){
            vmin->cor = -1;
            stackPush(pilha, vmin);
            removeVertice(graph, vmin);
            printf("Push: %d\n", vmin->id);
        }
        else{
            vmax->cor = -1;
            stackPush(pilha, vmax);
            removeVertice(graph, vmax);
            printf("Push: %d *\n", vmax->id);
        }
    }
    return pilha;
}

char* selectGrafo(Grafo* graph, Stack* stack, int k){
    char *resultado;
    int flag = 1;

    while(!stackIsEmpty(stack)){

        Vertice* vertice = stackPop(stack);
        addVertice(vertice, graph);
        
        if(flag){
            int cores[k], i;
            for(i = 0; i < k; i++){
                cores[i] = 1;
            }
            Aresta *a;
            for(a = vertice->primeiro; a != NULL; a = a->prox){
                if(a->vertice < k){
                    cores[a->vertice] = 0;
                }
                else{
                    Vertice *v;
                    for(v = graph->primeiro; v != NULL; v = v->prox){
                        if (v->id == a->vertice){
                            if (v->cor > -1){
                                cores[v->cor] = 0;
                            }
                            break;
                        }
                    }
                }
            }
            for(i = 0; i < k; i++){
                if(cores[i]){
                    vertice->cor = i;
                    break;
                }
            }
            if(vertice->cor < 0){
                flag = 0;
                printf("Pop: %d -> NO COLOR AVAILABLE\n", vertice->id);
                resultado = malloc(sizeof(char) * 6);
                strcpy(resultado, "SPILL");
            }
            else{
                //printf("%d", vertice->grau);
                printf("Pop: %d -> %d\n", vertice->id, vertice->cor);
            }
        }
    }
    if(flag){
        resultado = malloc(sizeof(char) * 22);
        strcpy(resultado, "Successful Allocation");
    }
    return resultado;
}