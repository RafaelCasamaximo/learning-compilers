#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"
#include "registerAllocation.h"

int main()
{
    RegisterAllocation* registerAllocation = createRegisterAllocation();
    fscanf(stdin, "Grafo %d:\nK=%d\n", &registerAllocation->graphNumber, &registerAllocation->physicalRegisters);
    startAllocationProcess(registerAllocation);
    deleteRegisterAllocation(registerAllocation);
    return 0;
}