#ifndef __STACK_H_
#define __STACK_H_

typedef void* Info;

typedef struct stackNode
{
    struct stackNode* previous;
    Info info;
}StackNode;

typedef struct stack
{
    StackNode* last;
    int size;
}Stack;

/*
    Aloca uma nova stack
*/
Stack* createStack();

/*
    Insere um novo elemento no topo da stack
*/
void pushStack(Stack* stack, Info info);

/*
    Remove o elemento do topo da stack e retorna a informação
*/
Info popStack(Stack* stack);

/*
    Remove todos os elementos da stack. Não remove a info.
*/
void removeAllElementsStack(Stack* stack);

/*
    Remove todos os elementos da stack e desaloca a stack.
*/
void deleteStack(Stack* stack);

#endif