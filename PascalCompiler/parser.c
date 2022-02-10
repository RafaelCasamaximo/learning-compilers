#include "stack.h"
#include "parser.h"

int programa(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case PROGRAM:
        pushStack(stack, PERIOD);
        pushStack(stack, BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, ID);
        pushStack(stack, PROGRAM);
        break;
    default:
        return 0;
    }
    return 1;
}

int bloco(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case PROCEDURE:
    case FUNCTION:
    case BEGIN_T:
        pushStack(stack, AUX_BLOCO_NT);
        break;
    case VAR:
        pushStack(stack, AUX_BLOCO_NT);
        pushStack(stack, CICLO_BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, TIPO_NT);
        pushStack(stack, COLON);
        pushStack(stack, CICLO2_BLOCO_NT);
        pushStack(stack, ID);
        pushStack(stack, VAR);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_bloco(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case PROCEDURE:
        pushStack(stack, AUX_BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, PROCEDURE);
        break;
    case FUNCTION:
        pushStack(stack, AUX_BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, ID);
        pushStack(stack, COLON);
        pushStack(stack, PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, FUNCTION);
        break;
    case BEGIN_T:
        pushStack(stack, END);
        pushStack(stack, CICLO2_COMANDO_NT);
        pushStack(stack, COMANDO_NT);
        pushStack(stack, BEGIN_T);
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_bloco(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case PROCEDURE:
    case FUNCTION:
    case BEGIN_T:
        break;
    case ID:
        pushStack(stack, CICLO_BLOCO_NT);
        pushStack(stack, SEMICOLON);
        pushStack(stack, TIPO_NT);
        pushStack(stack, COLON);
        pushStack(stack, CICLO2_BLOCO_NT);
        pushStack(stack, ID);
        break;
    default:

        return 0;
    }
    return 1;
}

int ciclo2_bloco(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case COLON:
        break;
    case COMMA:
        pushStack(stack, CICLO2_BLOCO_NT);
        pushStack(stack, ID);
        pushStack(stack, COMMA);
        break;
    default:

        return 0;
    }
    return 1;
}

int tipo(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
        pushStack(stack, ID);
        break;
    case ARRAY:
        pushStack(stack, TIPO_NT);
        pushStack(stack, OF);
        pushStack(stack, RBRACKET);
        pushStack(stack, CICLO_TIPO_NT);
        pushStack(stack, CONSTANTE_NT);
        pushStack(stack, PERIOD);
        pushStack(stack, PERIOD);
        pushStack(stack, CONSTANTE_NT);
        pushStack(stack, LBRACKET);
        pushStack(stack, ARRAY);
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_tipo(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case RBRACKET:
        break;
    case COMMA:
        pushStack(stack, CONSTANTE_NT);
        pushStack(stack, PERIOD);
        pushStack(stack, PERIOD);
        pushStack(stack, CONSTANTE_NT);
        pushStack(stack, COMMA);
        break;
    default:
        return 0;
    }
    return 1;
}

int parametros(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case SEMICOLON:
    case COLON:
        break;
    case LPAREN:
        pushStack(stack, RPAREN);
        pushStack(stack, AUX_PARAMETROS_NT);
        pushStack(stack, LPAREN);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_parametros(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
        pushStack(stack, END_PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, COLON);
        pushStack(stack, CICLO_PARAMETROS_NT);
        pushStack(stack, ID);
        break;
    case VAR:
        pushStack(stack, END_PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, COLON);
        pushStack(stack, CICLO_PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, VAR);
        break;
    default:
        return 0;
    }
    return 1;
}

int end_parametros(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case RPAREN:
        break;
    case SEMICOLON:
        pushStack(stack, AUX_PARAMETROS_NT);
        pushStack(stack, SEMICOLON);
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_parametros(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case COLON:
        break;
    case COMMA:
        pushStack(stack, CICLO_PARAMETROS_NT);
        pushStack(stack, ID);
        pushStack(stack, COMMA);
        break;
    default:
        return 0;
    }
    return 1;
}

int comando(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
        pushStack(stack, AUX_COMANDO_NT);
        pushStack(stack, ID);
        break;
    case SEMICOLON:
    case END:
        break;
    case BEGIN_T:
        pushStack(stack, END);
        pushStack(stack, CICLO2_COMANDO_NT);
        pushStack(stack, COMANDO_NT);
        pushStack(stack, BEGIN_T);
        break;
    case IF:
        pushStack(stack, AUX2_COMANDO_NT);
        pushStack(stack, END);
        pushStack(stack, CICLO2_COMANDO_NT);
        pushStack(stack, COMANDO_NT);
        pushStack(stack, BEGIN_T);
        pushStack(stack, THEN);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, IF);
        break;
    case WHILE:
        pushStack(stack, COMANDO_NT);
        pushStack(stack, DO);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, WHILE);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_comando(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ASSIGN:
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, ASSIGN);
        break;
    case LBRACKET:
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, ASSIGN);
        pushStack(stack, AUX_VARIAVEL_NT);
        break;
    case LPAREN:
        pushStack(stack, RPAREN);
        pushStack(stack, CICLO_COMANDO_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, LPAREN);
    case SEMICOLON:
    case END:
        break;
    default:
        return 0;
    }
    return 1;
}

int aux2_comando(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ELSE:
        pushStack(stack, END);
        pushStack(stack, CICLO2_COMANDO_NT);
        pushStack(stack, COMANDO_NT);
        pushStack(stack, BEGIN_T);
        pushStack(stack, ELSE);
    case SEMICOLON:
    case END:
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_comando(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case COMMA:
        pushStack(stack, CICLO_COMANDO_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, COMMA);
    case RPAREN:
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo2_comando(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case SEMICOLON:
        pushStack(stack, CICLO2_COMANDO_NT);
        pushStack(stack, COMANDO_NT);
        pushStack(stack, SEMICOLON);
        break;
    case END:
        break;
    default:
        return 0;
    }
    return 1;
}

int expressao(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ADD:
    case SUB:
    case ID:
    case NUMBER:
    case LPAREN:
    case LOG_NOT:
        pushStack(stack, END_EXPRESSAO_NT);
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        break;
    default:
        return 0;
    }
    return 1;
}

int expressao_simples(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ADD:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        pushStack(stack, ADD);
        break;
    case SUB:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        pushStack(stack, SUB);
        break;
    case ID:
    case NUMBER:
    case LPAREN:
    case LOG_NOT:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        break;
    default:
        return 0;
    }
    return 1;
}

int end_expressao_simples(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case SEMICOLON:
    case END:
    case COMMA:
    case RPAREN:
    case RBRACKET:
    case THEN:
    case DO:
    case EQUALS:
    case DIFF:
    case LESS:
    case LEQ:
    case GEQ:
    case GREAT:
        break;
    case ADD:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        pushStack(stack, ADD);
        break;
    case SUB:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        pushStack(stack, SUB);
        break;
    case LOG_OR:
        pushStack(stack, END_EXPRESSAO_SIMPLES_NT);
        pushStack(stack, TERMO_NT);
        pushStack(stack, LOG_OR);
        break;
    default:
        return 0;
    }
    return 1;
}

int end_expressao(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case END:
    case SEMICOLON:
    case RPAREN:
    case DO:
    case THEN:
    case COMMA:
    case RBRACKET:
        break;
    case EQUALS:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, EQUALS);
        break;
    case DIFF:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, DIFF);
        break;
    case LESS:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, LESS);
        break;
    case LEQ:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, LEQ);
        break;
    case GREAT:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, GREAT);
        break;
    case GEQ:
        pushStack(stack, EXPRESSAO_SIMPLES_NT);
        pushStack(stack, GEQ);
        break;
    default:
        return 0;
    }
    return 1;
}

int termo(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
    case NUMBER:
    case LPAREN:
    case LOG_NOT:
        pushStack(stack, AUX_TERMO_NT);
        pushStack(stack, FATOR_NT);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_termo(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case SEMICOLON:
    case END:
    case COMMA:
    case RPAREN:
    case RBRACKET:
    case THEN:
    case DO:
    case DIFF:
    case LESS:
    case LEQ:
    case GEQ:
    case GREAT:
    case EQUALS:
    case ADD:
    case SUB:
    case LOG_OR:
        break;
    case LOG_AND:
        pushStack(stack, AUX_TERMO_NT);
        pushStack(stack, FATOR_NT);
        pushStack(stack, LOG_AND);
        break;
    case MULT:
        pushStack(stack, AUX_TERMO_NT);
        pushStack(stack, FATOR_NT);
        pushStack(stack, MULT);
        break;
    case DIV:
        pushStack(stack, AUX_TERMO_NT);
        pushStack(stack, FATOR_NT);
        pushStack(stack, DIV);
        break;
    default:

        return 0;
    }
    return 1;
}

int fator(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
        pushStack(stack, AUX_FATOR_NT);
        pushStack(stack, ID);
        break;
    case NUMBER:
        pushStack(stack, NUMBER);
        break;
    case LPAREN:
        pushStack(stack, RPAREN);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, LPAREN);
        break;
    case LOG_NOT:
        pushStack(stack, FATOR_NT);
        pushStack(stack, LOG_NOT);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_fator(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case SEMICOLON:
    case END:
    case COMMA:
    case RPAREN:
    case RBRACKET:
    case THEN:
    case DO:
    case DIFF:
    case LESS:
    case LEQ:
    case GEQ:
    case GREAT:
    case EQUALS:
    case ADD:
    case SUB:
    case LOG_OR:
    case MULT:
    case DIV:
    case LOG_AND:
        break;
    case LBRACKET:
        pushStack(stack, AUX_VARIAVEL_NT);
        break;
    case LPAREN:
        pushStack(stack, RPAREN);
        pushStack(stack, CICLO_FATOR_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, LPAREN);
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_fator(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case COMMA:
        pushStack(stack, CICLO_FATOR_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, COMMA);
        break;
    case RPAREN:
        break;
    default:
        return 0;
    }
    return 1;
}

int variavel(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ID:
        pushStack(stack, AUX_VARIAVEL_NT);
        pushStack(stack, ID);
        break;
    default:
        return 0;
    }
    return 1;
}

int aux_variavel(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case LBRACKET:
        pushStack(stack, RBRACKET);
        pushStack(stack, CICLO_VARIAVEL_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, LBRACKET);
        break;
    default:
        return 0;
    }
    return 1;
}

int ciclo_variavel(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case COMMA:
        pushStack(stack, CICLO_VARIAVEL_NT);
        pushStack(stack, EXPRESSAO_NT);
        pushStack(stack, COMMA);
        break;
    case LBRACKET:
        break;
    default:
        return 0;
    }
    return 1;
}

int constante(Stack stack, int inputToken)
{
    switch (inputToken)
    {
    case ADD:
        pushStack(stack, NUMBER);
        pushStack(stack, ADD);
        break;
    case SUB:
        pushStack(stack, NUMBER);
        pushStack(stack, SUB);
        break;
    case NUMBER:
        pushStack(stack, NUMBER);
        break;
    default:
        return 0;
    }
    return 1;
}

int verifyToken(int token, int currentToken)
{
    if (currentToken == token)
    {
        return 1;
    }
    return 0;
}

int parser(Stack stack, int inputToken, int currentToken)
{
    switch (currentToken)
    {
    case PROGRAMA_NT:
        return programa(stack, inputToken);
    case BLOCO_NT:
        return bloco(stack, inputToken);
    case AUX_BLOCO_NT:
        return aux_bloco(stack, inputToken);
    case CICLO_BLOCO_NT:
        return ciclo_bloco(stack, inputToken);
    case CICLO2_BLOCO_NT:
        return ciclo2_bloco(stack, inputToken);
    case TIPO_NT:
        return tipo(stack, inputToken);
    case CICLO_TIPO_NT:
        return ciclo_tipo(stack, inputToken);
    case PARAMETROS_NT:
        return parametros(stack, inputToken);
    case AUX_PARAMETROS_NT:
        return aux_parametros(stack, inputToken);
    case END_PARAMETROS_NT:
        return end_parametros(stack, inputToken);
    case CICLO_PARAMETROS_NT:
        return ciclo_parametros(stack, inputToken);
    case COMANDO_NT:
        return comando(stack, inputToken);
    case AUX_COMANDO_NT:
        return aux_comando(stack, inputToken);
    case AUX2_COMANDO_NT:
        return aux2_comando(stack, inputToken);
    case CICLO_COMANDO_NT:
        return ciclo_comando(stack, inputToken);
    case CICLO2_COMANDO_NT:
        return ciclo2_comando(stack, inputToken);
    case EXPRESSAO_NT:
        return expressao(stack, inputToken);
    case EXPRESSAO_SIMPLES_NT:
        return expressao_simples(stack, inputToken);
    case END_EXPRESSAO_SIMPLES_NT:
        return end_expressao_simples(stack, inputToken);
    case END_EXPRESSAO_NT:
        return end_expressao(stack, inputToken);
    case TERMO_NT:
        return termo(stack, inputToken);
    case AUX_TERMO_NT:
        return aux_termo(stack, inputToken);
    case FATOR_NT:
        return fator(stack, inputToken);
    case AUX_FATOR_NT:
        return aux_fator(stack, inputToken);
    case CICLO_FATOR_NT:
        return ciclo_fator(stack, inputToken);
    case VARIAVEL_NT:
        return variavel(stack, inputToken);
    case AUX_VARIAVEL_NT:
        return aux_variavel(stack, inputToken);
    case CICLO_VARIAVEL_NT:
        return ciclo_variavel(stack, inputToken);
    case CONSTANTE_NT:
        return constante(stack, inputToken);
    default:
        return 0;
    }
}