#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"
#include "stack.h"
#include "parser.h"

#include "utility.h"
#include "lex.yy.c"

int main()
{
    // Saída base
    FILE *fileInput = stdin;
    // Stack
    Stack stack = createStack();
    // Tokens
    int inputToken;
    // Auxiliar de Impressão de Argumentos
    int firstFlag = 1;

    inputToken = advance();
    pushStack(stack, (void *)PROGRAMA_NT);

    while (inputToken != END_OF_FILE)
    {
        int currentToken = popStack(stack);

        if (currentToken > __START_TERMINAIS && currentToken < __END_TERMINAIS)
        {
            if (verifyToken(inputToken, currentToken))
            {
                inputToken = advance();
            }
            else
            {
                printfArgs(&firstFlag, "ERRO DE SINTAXE. Linha: %d -> \"%s\"", total_lines, yytext);
                removeStack(stack);
                exit(0);
            }
        }
        else if (currentToken > __START_NAO_TERMINAIS && currentToken < __END_NAO_TERMINAIS)
        {
            if (!parser(stack, inputToken, currentToken))
            {
                printfArgs(&firstFlag, "ERRO DE SINTAXE. Linha: %d -> \"%s\"", total_lines, yytext);
                removeStack(stack);
                exit(0);
            }
        }
        if (inputToken == OTHER)
        {
            printfArgs(&firstFlag, "ERRO LEXICO. Linha: %d Coluna: %d -> %s", total_lines, total_chars, yytext);
            removeStack(stack);
            exit(0);
        }
    }

    if (isEmptyStack(stack))
    {
        printfArgs(&firstFlag, "PROGRAMA CORRETO.");
    }
    removeStack(stack);

    return 0;
}