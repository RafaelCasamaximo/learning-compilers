#ifndef TOKENS_H_
#define TOKENS_H_

#include <stdio.h>
#include <stdint.h>

enum tokens
{

    /*Aux*/
    END_OF_FILE,
    OTHER,
    WHITESPACE,
    NEWLINE,

    /*Structures*/
    __START_TERMINAIS,
    PROGRAM,
    VAR,
    PROCEDURE,
    FUNCTION,
    BEGIN_T,
    END,
    ARRAY,
    OF,
    DO,
    WHILE,
    IF,
    THEN,
    ELSE,

    /*Math Operators*/
    ADD,
    SUB,
    MULT,
    DIV,

    /*Logical*/
    LOG_AND,
    LOG_OR,
    LOG_NOT,

    /*Logical Operators*/
    EQUALS,
    DIFF,
    LESS,
    GREAT,
    LEQ,
    GEQ,
    ASSIGN,

    /*Delimiters*/
    SEMICOLON,
    PERIOD,
    COMMA,
    COLON,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,

    /*Identificadores e Variáveis*/
    NUMBER,
    ID,
    __END_TERMINAIS,

    __START_NAO_TERMINAIS,
    PROGRAMA_NT,
    BLOCO_NT,
    AUX_BLOCO_NT,
    CICLO_BLOCO_NT,
    CICLO2_BLOCO_NT,
    CICLO3_BLOCO_NT,
    TIPO_NT,
    CICLO_TIPO_NT,
    PARAMETROS_NT,
    AUX_PARAMETROS_NT,
    END_PARAMETROS_NT,
    CICLO_PARAMETROS_NT,
    COMANDO_NT,
    AUX_COMANDO_NT,
    AUX2_COMANDO_NT,
    CICLO_COMANDO_NT,
    CICLO2_COMANDO_NT,
    EXPRESSAO_NT,
    EXPRESSAO_SIMPLES_NT,
    END_EXPRESSAO_SIMPLES_NT,
    END_EXPRESSAO_NT,
    TERMO_NT,
    AUX_TERMO_NT,
    FATOR_NT,
    AUX_FATOR_NT,
    CICLO_FATOR_NT,
    VARIAVEL_NT,
    AUX_VARIAVEL_NT,
    CICLO_VARIAVEL_NT,
    CONSTANTE_NT,
    __END_NAO_TERMINAIS
};

#endif