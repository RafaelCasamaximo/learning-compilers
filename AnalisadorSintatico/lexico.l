/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
#include <sintatico.tab.h>
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
    /*Estruturas*/
"void"		{total_chars += 4; return VOID;}
"int"		{total_chars += 3; return INT;}
"char"		{total_chars += 4; return CHAR;}
"return"	{total_chars += 6; return RETURN;}
"break"		{total_chars += 5; return BREAK;}
"switch"	{total_chars += 6; return SWITCH;}
"case"		{total_chars += 4; return CASE;}
"default"	{total_chars += 7; return DEFAULT;}
"do"		{total_chars += 2; return DO;}
"while"		{total_chars += 5; return WHILE;}
"for"		{total_chars += 3; return FOR;}
"if"		{total_chars += 2; return IF;}
"else"		{total_chars += 4; return ELSE;}
"typedef"	{total_chars += 7; return TYPEDEF;}
"struct"	{total_chars += 6; return STRUCT;}

    /*Operadores Matemático*/
"+"		    {total_chars++; return ADD;}
"-"		    {total_chars++; return SUB;}
"*"		    {total_chars++; return MULT;}
"/"		    {total_chars++; return DIV;}
"%"		    {total_chars++; return MOD;}
"++"	    {total_chars += 2; return INC;}
"--"	    {total_chars += 2; return DEC;}

    /*Bitwise*/
"&"		    {total_chars++; return BIT_AND;}
"|"		    {total_chars++; return BIT_OR;}
"~"		    {total_chars++; return BIT_NOT;}
"^"		    {total_chars++; return BIT_XOR;}

    /*Logicos*/
"&&"	    {total_chars += 2; return LOG_AND;}
"||"	    {total_chars += 2; return LOG_OR;}
"!"		    {total_chars++; return LOG_NOT;}
"=="	    {total_chars += 2; return EQUALS;}
"!="	    {total_chars += 2; return NOT_EQUALS;}
"<"		    {total_chars++; return LESS;}
">"		    {total_chars++; return GREAT;}
"<="	    {total_chars += 2; return LEQ;}
">="	    {total_chars += 2; return GEQ;}

    /*Shift*/
">>"	    {total_chars += 2; return RSHIFT;}
"<<"	    {total_chars += 2; return LSHIFT;}

    /*Assign*/
"="		    {total_chars++; return ASSIGN;}
"+="	    {total_chars += 2; return ADD_ASSIGN;}
"-="	    {total_chars += 2; return SUB_ASSIGN;}

    /*Funções*/
"printf"	{total_chars += 6; return PRINTF_T;}
"scanf"		{total_chars += 5; return SCANF_T;}
"exit"		{total_chars += 4; return EXIT_T;}
"#"			{total_chars++; return NUMBER_SIGN;}
"define"	{total_chars += 6; return DEFINE_T;}

    /*Delimitadores*/
";"		    {total_chars++; return SEMICOLON;}
","		    {total_chars++; return COMMA;}
":"		    {total_chars++; return COLON;}
"("		    {total_chars++; return LPAREN;}
")"		    {total_chars++; return RPAREN;}
"{"		    {total_chars++; return LCBRACK;}
"}"		    {total_chars++; return RCBRACK;}
"["		    {total_chars++; return LBRACK;}
"]"		    {total_chars++; return RBRACK;}
"?"		    {total_chars++; return QUEST_MARK;}
"->"	    {total_chars += 2; return POINTER_DEFERENCE;}

    /*Variáveis*/
"0"("x"|"X")([a-fA-F0-9])+		 {total_chars += strlen(yytext); return NUM_HEXA; }
"0"[1-7][0-7]*					 {total_chars += strlen(yytext); return NUM_OCTA;}
[0-9]+							 {total_chars += strlen(yytext); return NUM_INT;}
"\'""\\"?."\'"					 {total_chars += strlen(yytext); return CHARACTER;}
\"(\\.|[^"\\])*\"				 {total_chars += strlen(yytext); return STRING;}
([a-zA-Z]|"_")([a-zA-Z0-9]|"_")* {total_chars += strlen(yytext); return IDENTIFIER;}

    /*Comentarios*/
"//".*[\n]									{total_lines++; total_chars = 1;}
"//".*			                            {return END_OF_FILE;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*/")	{total_lines += countChar(yytext, '\n'); total_chars += strlen(yytext);}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)		{return UNTERMINATED_COMMENT;}

[ \r\t\f]									{total_chars++;}
[\n]										{total_lines++; total_chars = 1;}
<<EOF>>		                                {return END_OF_FILE;}
.											{total_chars++; return OTHER;}

%%
