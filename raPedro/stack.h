#ifndef DATASTRUCT_STACK_H
#define DATASTRUCT_STACK_H

typedef void* Info;

typedef struct StackNode{
	Info element;
	struct StackNode* prev;
}StackNode;

typedef struct stack{
	StackNode* top;
	int size;
}Stack;

Stack* stackCreate();

int stackPush(Stack*, Info);

Info stackPop(Stack*);

int stackIsEmpty(Stack*);

void stackDump(Stack*);

void stackFree(Stack*);


#endif