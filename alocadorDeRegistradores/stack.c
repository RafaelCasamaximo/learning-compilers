#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack()
{
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->last = NULL;
    return stack;
}

void pushStack(Stack* stack, Info info)
{
    StackNode* newNode = malloc(sizeof(StackNode));

    newNode->info = info;
    newNode->previous = stack->last;

    stack->last = newNode;
    stack->size++;
}

Info popStack(Stack* stack)
{
    if(stack->last == NULL)
    {
        return NULL;
    }

    Info poppedInfo = stack->last->info;
    StackNode* poppedNode = stack->last;

    stack->last = poppedNode->previous;

    free(poppedNode);
    stack->size--;

    return poppedInfo;
}

void removeAllElementsStack(Stack* stack)
{
    StackNode* lastNode = stack->last;

    while(lastNode != NULL)
    {
        StackNode* aux = lastNode->previous;
        lastNode->previous = NULL;
        free(lastNode);
        lastNode = aux;
    }

    stack->last = NULL;
    stack->size = 0;
}

void deleteStack(Stack* stack)
{
    removeAllElementsStack(stack);
    free(stack);
}