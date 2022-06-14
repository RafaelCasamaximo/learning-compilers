#ifndef __regAlloc__
#define __regAlloc__

#include <stdio.h>
#include "grafo.h"
#include "stack.h"

Grafo* build(FILE* file);

Stack* simplify(Grafo* graph, int k);

char* selectGrafo(Grafo* graph, Stack* stack, int k);

#endif