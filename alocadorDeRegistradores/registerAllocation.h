#ifndef __REGISTERALLOCATION_H_
#define __REGISTERALLOCATION_H_

#include "graph.h"
#include "stack.h"

typedef struct registerAllocation
{
    int graphNumber;
    int physicalRegisters;
    Graph* graph;
}RegisterAllocation;

RegisterAllocation* createRegisterAllocation();
void deleteRegisterAllocation(RegisterAllocation* registerAllocation);
void startAllocationProcess(RegisterAllocation* registerAllocation);
void buildGraph(RegisterAllocation* registerAllocation);
Stack* simplifyGraph(Graph* graph, int k);
char* selectGraph(Graph* graph, Stack* stack, int k);

#endif