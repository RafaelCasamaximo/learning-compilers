#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registerAllocation.h"
#include "graph.h"
#include "stack.h"

RegisterAllocation* createRegisterAllocation()
{
    RegisterAllocation* registerAllocation = malloc(sizeof(RegisterAllocation));
    registerAllocation->graph = NULL;
    registerAllocation->graphNumber = -1;
    registerAllocation->physicalRegisters -1;

    return registerAllocation;
}

void deleteRegisterAllocation(RegisterAllocation* registerAllocation)
{
    free(registerAllocation);
}

void startAllocationProcess(RegisterAllocation* registerAllocation)
{
    buildGraph(registerAllocation);

    char* results[registerAllocation->physicalRegisters - 1];

    printf("Graph %d -> Physical Registers: %d\n", registerAllocation->graphNumber, registerAllocation->physicalRegisters);
    printf("----------------------------------------\n");
    printf("----------------------------------------\n");

    for(int k = registerAllocation->physicalRegisters; k > 1; k--)
    {
        printf("K = %d\n\n", k);
        Stack* stack = simplifyGraph(registerAllocation->graph, k);
        results[k - 1] = selectGraph(registerAllocation->graph, stack, k);
        printf("----------------------------------------\n");
        deleteStack(stack);
    }

    printf("----------------------------------------");

    for(int k = registerAllocation->physicalRegisters; k > 1; k--)
    {
        printf("\nGraph %d -> K = %2d: %s", registerAllocation->graphNumber, k, results[k - 1]);
    }
}

void buildGraph(RegisterAllocation* registerAllocation)
{
    registerAllocation->graph = createGraph();

    int vertexId;
    while(fscanf(stdin, "%d -->", &vertexId) != EOF)
    {
        Vertex* vertex = createVertex(vertexId);

        char c = fgetc(stdin);
        while(c == ' ')
        {
            int edgeNumber;
            fscanf(stdin, "%d", &edgeNumber);
            insertEdgeVertexGraph(vertex, edgeNumber);
            c = fgetc(stdin);
        }
        insertVertexGraph(registerAllocation->graph, vertex);
    }
}

Stack* simplifyGraph(Graph* graph, int k)
{
    Stack* stack = createStack();

    int n = graph->vertexNumber;
    for(int i = 0; i < n; i++)
    {
        // Vertices máximos e mínimos
        // For
        Vertex* minimumVertex = NULL;
        Vertex* maximumVertex = NULL;
        int min = 0, max = 0;
        for(Vertex* auxVertex = graph->first; auxVertex != NULL; auxVertex = auxVertex->next)
        {
            int edgesNumber = auxVertex->degree;
            
            // Atualiza minimo e máximo e compara com o número de arestas
            if(minimumVertex == NULL || edgesNumber < min)
            {
                minimumVertex = auxVertex;
                min = edgesNumber;
            }
            else if(edgesNumber == min && minimumVertex->id > auxVertex->id)
            {
                minimumVertex = auxVertex;
            }

            if(maximumVertex == NULL || edgesNumber > max)
            {
                maximumVertex = auxVertex;
                max = edgesNumber;
            }
            else if(edgesNumber == max && maximumVertex->id > auxVertex->id)
            {
                maximumVertex = auxVertex;
            }
        }
        // If
        //Else
        if(min < k)
        {
            minimumVertex->color = -1;
            pushStack(stack, minimumVertex);
            removeVertexGraph(graph, minimumVertex);
            printf("Push: %d\n", minimumVertex->id);
        }
        else
        {
            maximumVertex->color = -1;
            pushStack(stack, maximumVertex);
            removeVertexGraph(graph, maximumVertex);
            printf("Push: %d *\n", maximumVertex->id);
        }
    }

    return stack;
}

char* selectGraph(Graph* graph, Stack* stack, int k)
{
    char* result;
    int success = 1;

    while(stack->size > 0)
    {
        Vertex* auxVertex = popStack(stack);
        insertVertexGraph(graph, auxVertex);

        if(!success)
        {
            continue;
        }

        int colors[k];
        for(int i = 0; i < k; i++)
        {
            colors[i] = 1;
        }

        Edge *a;
        for(a = auxVertex->first; a != NULL; a = a->next){
            if(a->vertexId < k){
                colors[a->vertexId] = 0;
            }
            else{
                Vertex *v;
                for(v = graph->first; v != NULL; v = v->next){
                    if (v->id == a->vertexId){
                        if (v->color > -1){
                            colors[v->color] = 0;
                        }
                        break;
                    }
                }
            }
        }

        for(int i = 0; i < k; i++)
        {
            if(colors[i])
            {
                auxVertex->color = i;
                break;
            }
        }

        if(auxVertex->color < 0)
        {
            success = 0;
            printf("Pop: %d -> NO COLOR AVAILABLE\n", auxVertex->id);
            result = malloc(sizeof(char) * 50);
            strcpy(result, "SPILL");
        }
        else
        {
            printf("Pop: %d -> %d\n", auxVertex->id, auxVertex->color);
        }
    }

    if(success)
    {
        result = malloc(sizeof(char) * 50);
        strcpy(result, "Successful Allocation");
    }

    return result;
}
