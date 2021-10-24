/* Nao usar a biblioteca do flex*/
%option noyywrap


%{
#include<stdarg.h>

    int total_lines = 1;
    int line_chars = 0;

    int firstFlag = 1;

    int countChar(char* content, char id){
        int frequency = 0;
        for(int i = 0; i < strlen(content); i++){
            if(content[i] == id){
                frequency++;
            }
        }
        return frequency;
    }


%}

%%

    /*Estructures*/
"void"                                          {printf("VOID"); line_chars += 4;}
"int"                                           {printf("INT"); line_chars += 3;}
"char"                                          {printf("CHAR"); line_chars += 4;}
"return"                                        {printf("RETURN"); line_chars += 6;}
"break"                                         {printf("BREAK"); line_chars += 5;}
"switch"                                        {printf("SWITCH"); line_chars += 6;}
"case"                                          {printf("CASE"); line_chars += 4;}
"default"                                       {printf("DEFAULT"); line_chars += 7;}
"do"                                            {printf("DO"); line_chars += 2;}
"while"                                         {printf("WHILE"); line_chars += 5;}
"for"                                           {printf("FOR"); line_chars += 3;}
"if"                                            {printf("IF"); line_chars += 2;}
"else"                                          {printf("ELSE"); line_chars += 4;}
"typedef"                                       {printf("TYPEDEF"); line_chars += 7;}
"struct"                                        {printf("STRUCT"); line_chars += 6;}

    /*Math Operators*/
"+"                                             {printf("PLUS"); line_chars += 1;}
"-"                                             {printf("MINUS"); line_chars += 1;}
"*"                                             {printf("MULTIPLY"); line_chars += 1;}
"/"                                             {printf("DIV"); line_chars += 1;}
"%"                                             {printf("REMAINDER"); line_chars += 1;}
"++"                                            {printf("INC"); line_chars += 2;}
"--"                                            {printf("DEC"); line_chars += 2;}

    /*Bitwise*/
"&"                                             {printf("BITWISE_AND"); line_chars += 1;}
"|"                                             {printf("BITWISE_OR"); line_chars += 1;}
"~"                                             {printf("BITWISE_NOT"); line_chars += 1;}
"^"                                             {printf("BITWISE_XOR"); line_chars += 1;}

    /*Logical*/
"!"                                             {printf("NOT"); line_chars += 1;}
"&&"                                            {printf("LOGICAL_AND"); line_chars += 2;}
"||"                                            {printf("LOGICAL_OR"); line_chars += 2;}
"=="                                            {printf("EQUAL"); line_chars += 2;}
"!="                                            {printf("NOT_EQUAL"); line_chars += 2;}
"<"                                             {printf("LESS_THAN"); line_chars += 1;}
">"                                             {printf("GREATER_THAN"); line_chars += 1;}
"<="                                            {printf("LESS_EQUAL"); line_chars += 2;}
">="                                            {printf("GREATER_EQUAL"); line_chars += 2;}

    /*Shift*/
">>"                                            {printf("R_SHIFT"); line_chars += 2;}
"<<"                                            {printf("L_SHIFT"); line_chars += 2;}

    /*Assign*/
"="                                             {printf("ASSIGN"); line_chars += 1;}
"+="                                            {printf("ADD_ASSIGN"); line_chars += 2;}
"-="                                            {printf("MINUS_ASSIGN"); line_chars += 2;}

    /*Delimiters*/
";"                                             {printf("SEMICOLON"); line_chars += 1;}
","                                             {printf("COMMA"); line_chars += 1;}
":"                                             {printf("COLON"); line_chars += 1;}
"("                                             {printf("L_PAREN"); line_chars += 1;}
")"                                             {printf("R_PAREN"); line_chars += 1;}
"{"                                             {printf("L_CURLY_BRACKET"); line_chars += 1;}
"}"                                             {printf("R_CURLY_BRACKET"); line_chars += 1;}
"["                                             {printf("L_SQUARE_BRACKET"); line_chars += 1;}
"]"                                             {printf("R_SQUARE_BRACKET"); line_chars += 1;}
"?"                                             {printf("TERNARY_CONDITION"); line_chars += 1;}
"#"                                             {printf("NUMBER_SIGN"); line_chars += 1;}
"->"                                            {printf("POINTER"); line_chars += 2;}
comment
    /*Functions*/
"printf"                                        {printf("PRINTF"); line_chars += 6;}
"scanf"                                         {printf("SCANF"); line_chars += 5;}
"define"                                        {printf("DEFINE"); line_chars += 6;}
"exit"                                          {printf("EXIT"); line_chars += 4;}

    /*Variables*/
"0"("x"|"X")([0-9]|[A-F]|[a-f])+                {printf("NUM_HEXA(%s)", yytext); line_chars += strlen(yytext);}
"0"[1-7][0-7]*                                  {printf("NUM_OCTAL(%s)", yytext); line_chars += strlen(yytext);}
[0-9]+                                          {printf("NUM_INTEGER(%s)", yytext); line_chars += strlen(yytext);}
"\'""\\"?."\'"                                  {printf("CHARACTER("); strlen(yytext) == 3 ? printf("%c)", yytext[1]) : printf("%c%c)", yytext[1], yytext[2]); line_chars += strlen(yytext);}
\"(\\.|[^"\\])*\"                               {line_chars += strlen(yytext); yytext[strlen(yytext) - 1] = '\0'; char* aux = &yytext[1]; printf("STRING(%s)", aux); line_chars += strlen(yytext);}
[_a-zA-Z][_a-zA-Z0-9]*                          {printf("IDENTIFIER(%s)", yytext); line_chars += strlen(yytext);}

    /*Comments*/
"//".*[\n]                                      {total_lines += 1; line_chars = 0;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")    {total_lines += countChar(yytext, '\n');}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)           {printf("error:lexical:%d:%d: unterminated comment\n", total_lines, line_chars);}

    /*Others*/
[ \r\t\f]                                        {line_chars += 1;}
[\n]                                            {total_lines += 1; line_chars = 0;}
.                                               {line_chars += 1; printf("error:lexical:%d:%d: %s\n", total_lines, line_chars, yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
}
