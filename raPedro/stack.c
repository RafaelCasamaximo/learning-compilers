#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

Stack* stackCreate(){
	Stack *s = malloc(sizeof(Stack));
	if(s == NULL){
		return NULL;
	}
	s->size = 0;
	s->top = NULL;
	return s;
}

int stackPush(Stack* stack, Info elem){

	StackNode *aux = malloc(sizeof(StackNode));

	aux->element = elem;
	aux->prev = stack->top;
	stack->top = aux;
	stack->size++;
	return 0;
}

Info stackPop(Stack* stack){
	if(stack->top == NULL){
		return NULL;
	}
    
	Info info;
	StackNode *aux = stack->top;

	info = aux->element;
	stack->top = stack->top->prev;
	free(aux);
	
	stack->size--;
	return info;
}

int stackIsEmpty(Stack* stack){
	return stack->size == 0 ? 1 : 0;
}

int stackSize(Stack* stack){
	return stack->size;
}

void stackDump(Stack* stack){
	StackNode *node = stack->top;
    StackNode *aux;

	while(node != NULL){
		aux = node->prev;
		node->prev = NULL;
		free(node);
		node = aux;
	}

	stack->top = NULL;
	stack->size = 0;
}

void stackFree(Stack* stack){
	stackDump(stack);
	free(stack);
}