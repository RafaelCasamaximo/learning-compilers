#include <stdio.h>
#include "grafo.h"
#include "stack.h"
#include "alocador.h"

int main(){
    FILE* input = stdin;
    int nGrafo, nReg, k;
    fscanf(input, "Grafo %d:\nK=%d\n", &nGrafo, &nReg);
    Grafo* grafo = build(input);
    char* resultados[nReg - 1];
    printf("Graph %d -> Physical Registers: %d\n", nGrafo, nReg);
    printf("----------------------------------------\n----------------------------------------\n");
    for(k = nReg; k > 1; k--){
        printf("K = %d\n\n", k);
        Stack* pilha = simplify(grafo, k);
        resultados[k - 1] = selectGrafo(grafo, pilha, k);
        printf("----------------------------------------\n");
        stackFree(pilha);
    }
    printf("----------------------------------------");
    for(k = nReg; k > 1; k--){
        printf("\nGraph %d -> K = %2d: %s", nGrafo, k, resultados[k - 1]);
    }
    removeGrafo(grafo);
    return 0;
}