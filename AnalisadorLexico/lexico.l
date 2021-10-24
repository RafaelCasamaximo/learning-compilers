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

    void printfArgs(int flagDisableNl, char* format, ...){
        if(firstFlag == 1 || flagDisableNl == 1){
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            firstFlag = 0;
        }
        else{
            va_list args;
            va_start(args, format);
            printf("\n");
            vprintf(format, args);
            va_end(args);
        }
    }

%}

%%

    /*Estructures*/
"void"                                          {printfArgs(0, "VOID"); line_chars += 4;}
"int"                                           {printfArgs(0, "INT"); line_chars += 3;}
"char"                                          {printfArgs(0, "CHAR"); line_chars += 4;}
"return"                                        {printfArgs(0, "RETURN"); line_chars += 6;}
"break"                                         {printfArgs(0, "BREAK"); line_chars += 5;}
"switch"                                        {printfArgs(0, "SWITCH"); line_chars += 6;}
"case"                                          {printfArgs(0, "CASE"); line_chars += 4;}
"default"                                       {printfArgs(0, "DEFAULT"); line_chars += 7;}
"do"                                            {printfArgs(0, "DO"); line_chars += 2;}
"while"                                         {printfArgs(0, "WHILE"); line_chars += 5;}
"for"                                           {printfArgs(0, "FOR"); line_chars += 3;}
"if"                                            {printfArgs(0, "IF"); line_chars += 2;}
"else"                                          {printfArgs(0, "ELSE"); line_chars += 4;}
"typedef"                                       {printfArgs(0, "TYPEDEF"); line_chars += 7;}
"struct"                                        {printfArgs(0, "STRUCT"); line_chars += 6;}

    /*Math Operators*/
"+"                                             {printfArgs(0, "PLUS"); line_chars += 1;}
"-"                                             {printfArgs(0, "MINUS"); line_chars += 1;}
"*"                                             {printfArgs(0, "MULTIPLY"); line_chars += 1;}
"/"                                             {printfArgs(0, "DIV"); line_chars += 1;}
"%"                                             {printfArgs(0, "REMAINDER"); line_chars += 1;}
"++"                                            {printfArgs(0, "INC"); line_chars += 2;}
"--"                                            {printfArgs(0, "DEC"); line_chars += 2;}

    /*Bitwise*/
"&"                                             {printfArgs(0, "BITWISE_AND"); line_chars += 1;}
"|"                                             {printfArgs(0, "BITWISE_OR"); line_chars += 1;}
"~"                                             {printfArgs(0, "BITWISE_NOT"); line_chars += 1;}
"^"                                             {printfArgs(0, "BITWISE_XOR"); line_chars += 1;}

    /*Logical*/
"!"                                             {printfArgs(0, "NOT"); line_chars += 1;}
"&&"                                            {printfArgs(0, "LOGICAL_AND"); line_chars += 2;}
"||"                                            {printfArgs(0, "LOGICAL_OR"); line_chars += 2;}
"=="                                            {printfArgs(0, "EQUAL"); line_chars += 2;}
"!="                                            {printfArgs(0, "NOT_EQUAL"); line_chars += 2;}
"<"                                             {printfArgs(0, "LESS_THAN"); line_chars += 1;}
">"                                             {printfArgs(0, "GREATER_THAN"); line_chars += 1;}
"<="                                            {printfArgs(0, "LESS_EQUAL"); line_chars += 2;}
">="                                            {printfArgs(0, "GREATER_EQUAL"); line_chars += 2;}

    /*Shift*/
">>"                                            {printfArgs(0, "R_SHIFT"); line_chars += 2;}
"<<"                                            {printfArgs(0, "L_SHIFT"); line_chars += 2;}

    /*Assign*/
"="                                             {printfArgs(0, "ASSIGN"); line_chars += 1;}
"+="                                            {printfArgs(0, "ADD_ASSIGN"); line_chars += 2;}
"-="                                            {printfArgs(0, "MINUS_ASSIGN"); line_chars += 2;}

    /*Delimiters*/
";"                                             {printfArgs(0, "SEMICOLON"); line_chars += 1;}
","                                             {printfArgs(0, "COMMA"); line_chars += 1;}
":"                                             {printfArgs(0, "COLON"); line_chars += 1;}
"("                                             {printfArgs(0, "L_PAREN"); line_chars += 1;}
")"                                             {printfArgs(0, "R_PAREN"); line_chars += 1;}
"{"                                             {printfArgs(0, "L_CURLY_BRACKET"); line_chars += 1;}
"}"                                             {printfArgs(0, "R_CURLY_BRACKET"); line_chars += 1;}
"["                                             {printfArgs(0, "L_SQUARE_BRACKET"); line_chars += 1;}
"]"                                             {printfArgs(0, "R_SQUARE_BRACKET"); line_chars += 1;}
"?"                                             {printfArgs(0, "TERNARY_CONDITION"); line_chars += 1;}
"#"                                             {printfArgs(0, "NUMBER_SIGN"); line_chars += 1;}
"->"                                            {printfArgs(0, "POINTER"); line_chars += 2;}
comment
    /*Functions*/
"printf"                                        {printfArgs(0, "PRINTF"); line_chars += 6;}
"scanf"                                         {printfArgs(0, "SCANF"); line_chars += 5;}
"define"                                        {printfArgs(0, "DEFINE"); line_chars += 6;}
"exit"                                          {printfArgs(0, "EXIT"); line_chars += 4;}

    /*Variables*/
"0"("x"|"X")([0-9]|[A-F]|[a-f])+                {printfArgs(0, "NUM_HEXA(%s)", yytext); line_chars += strlen(yytext);}
"0"[1-7][0-7]*                                  {printfArgs(0, "NUM_OCTAL(%s)", yytext); line_chars += strlen(yytext);}
[0-9]+                                          {printfArgs(0, "NUM_INTEGER(%s)", yytext); line_chars += strlen(yytext);}
"\'""\\"?."\'"                                  {printfArgs(0, "CHARACTER("); strlen(yytext) == 3 ? printfArgs(1, "%c)", yytext[1]) : printfArgs(1, "%c%c)", yytext[1], yytext[2]); line_chars += strlen(yytext);}
\"(\\.|[^"\\])*\"                               {line_chars += strlen(yytext); yytext[strlen(yytext) - 1] = '\0'; char* aux = &yytext[1]; printfArgs(0, "STRING(%s)", aux);}
[_a-zA-Z][_a-zA-Z0-9]*                          {printfArgs(0, "IDENTIFIER(%s)", yytext); line_chars += strlen(yytext);}

    /*Comments*/
"//".*[\n]                                      {total_lines += 1; line_chars = 0;}
("/*"([^*]|[ \n]|("*"+([^*/]|[ \n])))*"*"+"/")	{total_lines += countChar(yytext, '\n'); line_chars += strlen(yytext);}
("/*"([^*]|[ \n]|("*"+([^*/]|[ \n])))*)         {printfArgs(0, "error:lexical:%d:%d: unterminated comment", total_lines, line_chars+1);}

    /*Others*/
[ \r\t\f]                                        {line_chars += 1;}
[\n]                                            {total_lines += 1; line_chars = 0;}
.                                               {line_chars += 1; printfArgs(0, "error:lexical:%d:%d: %s", total_lines, line_chars, yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
}
