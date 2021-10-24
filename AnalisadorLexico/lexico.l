/* Nao usar a biblioteca do flex*/
%option noyywrap


%{
#include<stdarg.h>

    int total_lines = 1;
    int line_chars = 0;

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
"void"                                          {printf("VOID\n"); line_chars += 4;}
"int"                                           {printf("INT\n"); line_chars += 3;}
"char"                                          {printf("CHAR\n"); line_chars += 4;}
"return"                                        {printf("RETURN\n"); line_chars += 6;}
"break"                                         {printf("BREAK\n"); line_chars += 5;}
"switch"                                        {printf("SWITCH\n"); line_chars += 6;}
"case"                                          {printf("CASE\n"); line_chars += 4;}
"default"                                       {printf("DEFAULT\n"); line_chars += 7;}
"do"                                            {printf("DO\n"); line_chars += 2;}
"while"                                         {printf("WHILE\n"); line_chars += 5;}
"for"                                           {printf("FOR\n"); line_chars += 3;}
"if"                                            {printf("IF\n"); line_chars += 2;}
"else"                                          {printf("ELSE\n"); line_chars += 4;}
"typedef"                                       {printf("TYPEDEF\n"); line_chars += 7;}
"struct"                                        {printf("STRUCT\n"); line_chars += 6;}

    /*Math Operators*/
"+"                                             {printf("PLUS\n"); line_chars += 1;}
"-"                                             {printf("MINUS\n"); line_chars += 1;}
"*"                                             {printf("MULTIPLY\n"); line_chars += 1;}
"/"                                             {printf("DIV\n"); line_chars += 1;}
"%"                                             {printf("REMINDER\n"); line_chars += 1;}
"++"                                            {printf("INC\n"); line_chars += 2;}
"--"                                            {printf("DEC\n"); line_chars += 2;}

    /*Bitwise*/
"&"                                             {printf("BITWISE_AND\n"); line_chars += 1;}
"|"                                             {printf("BITWISE_OR\n"); line_chars += 1;}
"~"                                             {printf("BITWISE_NOT\n"); line_chars += 1;}
"^"                                             {printf("BITWISE_XOR\n"); line_chars += 1;}

    /*Logical*/
"!"                                             {printf("NOT\n"); line_chars += 1;}
"&&"                                            {printf("LOGICAL_AND\n"); line_chars += 2;}
"||"                                            {printf("LOGICAL_OR\n"); line_chars += 2;}
"=="                                            {printf("EQUAL\n"); line_chars += 2;}
"!="                                            {printf("NOT_EQUAL\n"); line_chars += 2;}
"<"                                             {printf("LESS_THAN\n"); line_chars += 1;}
">"                                             {printf("GREATER_THAN\n"); line_chars += 1;}
"<="                                            {printf("LESS_EQUAL\n"); line_chars += 2;}
">="                                            {printf("GREATER_EQUAL\n"); line_chars += 2;}

    /*Shift*/
">>"                                            {printf("R_SHIFT\n"); line_chars += 2;}
"<<"                                            {printf("L_SHIFT\n"); line_chars += 2;}

    /*Assign*/
"="                                             {printf("ASSIGN\n"); line_chars += 1;}
"+="                                            {printf("ADD_ASSIGN\n"); line_chars += 2;}
"-="                                            {printf("MINUS_ASSIGN\n"); line_chars += 2;}

    /*Delimiters*/
";"                                             {printf("SEMICOLON\n"); line_chars += 1;}
","                                             {printf("COMMA\n"); line_chars += 1;}
":"                                             {printf("COLON\n"); line_chars += 1;}
"("                                             {printf("L_PAREN\n"); line_chars += 1;}
")"                                             {printf("R_PAREN\n"); line_chars += 1;}
"{"                                             {printf("L_CURLY_BRACKET\n"); line_chars += 1;}
"}"                                             {printf("R_CURLY_BRACKET\n"); line_chars += 1;}
"["                                             {printf("L_SQUARE_BRACKET\n"); line_chars += 1;}
"]"                                             {printf("R_SQUARE_BRACKET\n"); line_chars += 1;}
"?"                                             {printf("TERNARY_CONDITION\n"); line_chars += 1;}
"#"                                             {printf("NUMBER_SIGN\n"); line_chars += 1;}
"->"                                            {printf("POINTER\n"); line_chars += 2;}

    /*Functions*/
"printf"                                        {printf("PRINTF\n"); line_chars += 6;}
"scanf"                                         {printf("SCANF\n"); line_chars += 5;}
"define"                                        {printf("DEFINE\n"); line_chars += 6;}
"exit"                                          {printf("EXIT\n"); line_chars += 4;}

    /*Variables*/
[_a-zA-Z][_a-zA-Z0-9]*                          {printf("IDENTIFIER(%s)\n", yytext); line_chars += strlen(yytext);}
[0-9]+                                          {printf("NUM_INTEGER(%s)\n", yytext); line_chars += strlen(yytext);}
"0"[0-7]+                                       {printf("NUM_OCTAL(%s)\n", yytext); line_chars += strlen(yytext);}
"0"("X"|"x")([0-9]|[a-f]|[A-F])+                {printf("NUM_HEXA(%s)\n", yytext); line_chars += strlen(yytext);}
\"(\\.|[^"\\])*\"                               {line_chars += strlen(yytext); yytext[strlen(yytext) - 1] = '\0'; char* aux = &yytext[1]; printf("STRING(%s)", aux); line_chars += strlen(yytext);}
"\'""\\"?."\'"                                  {printf("CHARACTER("); strlen(yytext) == 3 ? printf("%c)", yytext[1]) : printf("%c%c)", yytext[1], yytext[2]); line_chars += strlen(yytext);}

    /*Comments*/
"//".*[\n]                                      {total_lines += 1; line_chars = 0;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")    {total_lines += countChar(yytext, '\n');}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)           {printf("error:lexical:%d:%d: unterminated comment", total_lines, line_chars);}

    /*Others*/
[\r\t\f]                                        {line_chars += 1;}
[\n]                                            {total_lines += 1; line_chars = 0;}
.                                               {line_chars += 1; printf("error:lexical:%d:%d: %s", total_lines, line_chars, yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
}
