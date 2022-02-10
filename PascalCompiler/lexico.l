%option noyywrap
%option case-insensitive

%{

#include "tokens.h"
#include <string.h>

int total_lines = 1;
int total_chars = 1;


int countChar(char* content, char id)
{

    int frequency = 0;

    for(int i = 0; i < strlen(content); i++)
    {
        if(content[i] == id)
        {
            frequency++;
        }
    }
    return frequency;
}

%}

%%

    /*Structures*/
"program"                                                   {total_chars += 7; return PROGRAM;}
"var"                                                       {total_chars += 3; return VAR;}
"procedure"                                                 {total_chars += 9; return PROCEDURE;}
"function"                                                  {total_chars += 8; return FUNCTION;}
"begin"                                                     {total_chars += 5; return BEGIN_T;}
"end"                                                       {total_chars += 3; return END;}
"array"                                                     {total_chars += 5; return ARRAY;}
"of"                                                        {total_chars += 2; return OF;}
"do"                                                        {total_chars += 2; return DO;}
"while"                                                     {total_chars += 5; return WHILE;}
"if"                                                        {total_chars += 2; return IF;}
"then"                                                      {total_chars += 4; return THEN;}
"else"                                                      {total_chars += 4; return ELSE;}

    /*Math Operators*/
"+"                                                         {total_chars += 1; return ADD;}
"-"                                                         {total_chars += 1; return SUB;}
"*"                                                         {total_chars += 1; return MULT;}
"div"                                                       {total_chars += 3; return DIV;}

    /*Logical*/
"and"                                                       {total_chars += 3; return LOG_AND;}
"or"                                                        {total_chars += 2; return LOG_OR;}
"not"                                                       {total_chars += 3; return LOG_NOT;}

    /*Logical Operators*/
"="                                                         {total_chars += 1; return EQUALS;}
"<>"                                                        {total_chars += 2; return DIFF;}
"<"                                                         {total_chars += 1; return LESS;}
">"                                                         {total_chars += 1; return GREAT;}
"<="                                                        {total_chars += 2; return LEQ;}
">="                                                        {total_chars += 2; return GEQ;}
":="                                                        {total_chars += 2; return ASSIGN;}

    /*Delimiters*/
";"                                                         {total_chars += 1; return SEMICOLON;}
"."                                                         {total_chars += 1; return PERIOD;}
","                                                         {total_chars += 1; return COMMA;}
":"                                                         {total_chars += 1; return COLON;}
"("                                                         {total_chars += 1; return LPAREN;}
")"                                                         {total_chars += 1; return RPAREN;}
"["                                                         {total_chars += 1; return LBRACKET;}
"]"                                                         {total_chars += 1; return RBRACKET;}

    /*Identificadores e Variáveis*/
[0-9]+                                                      {total_chars += strlen(yytext); return NUMBER;}
[a-zA-Z_][a-zA-Z0-9_]*                                      {total_chars += strlen(yytext); return ID;}
("(*"([^*]|[ \n]|("*"+([^*/]|[ \n])))*"*"+")")              {total_lines += countChar(yytext, '\n'); total_chars += strlen(yytext);}
"{"[^"}"]*"}"                                               {total_lines += countChar(yytext, '\n'); total_chars += strlen(yytext);}
[ \r\t\f]                                                   {total_chars += 1;}
[\n]                                                        {total_lines += 1; total_chars = 1;}
<<EOF>>                                                     {return END_OF_FILE;}
.                                                           {return OTHER;}


%%

int advance()
{
    int token;
    do
    {
        token = yylex();
    } while (token == WHITESPACE);
    return token;
}