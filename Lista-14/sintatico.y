%{
#include <stdio.h>
#include <string.h>
#include<stdarg.h>

extern int yylex();
extern char* yytext;
void yyerror(char *s);
extern int col;

void print_first_line(const char *format, ...);
void print_saida(const char *format, ...);
void (*print_resultado)(const char *format, ...) = print_first_line;

void print_first_line(const char *format, ...){
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	print_resultado = print_saida;
}

void print_saida(const char *format, ...){
	va_list args;
	va_start(args, format);
	printf("\n");
	vprintf(format, args);
	va_end(args);
}
%}

%token ADD
%token SUB
%token MUL
%token DIV
%token POW
%token MOD
%token SEN
%token COS
%token TAN
%token ABS
%token LPAREN
%token RPAREN
%token NUM
%token REAL
%token VAR
%token OTHER
%token EOL
%token END_OF_FILE

%start calclist

%%

calclist: exp EOL 			{print_resultado("EXPRESSAO CORRETA"); return 0;}
		| exp END_OF_FILE   {print_resultado("EXPRESSAO CORRETA"); return -1;}
;

exp: term			        { }
	| exp ADD exp           { }
	| exp SUB exp           { }
	| exp MUL exp           { }
	| exp DIV exp           { }
	| exp MOD exp           { }
	| exp POW exp           { }
	| ADD exp		        { }
	| SUB exp		        { }	        
	| SEN LPAREN exp RPAREN { }
	| COS LPAREN exp RPAREN { }
	| TAN LPAREN exp RPAREN { }
	| ABS LPAREN exp RPAREN { }
	| LPAREN exp RPAREN     { }
;

term: NUM	{ }
	| REAL	{ }
	| VAR	{ }
;

%%

void yyerror(char *s)
{
	col = col - strlen(yytext) + 1;
	if(*yytext == '\n' || *yytext == EOF){
		print_resultado("A expressao terminou de forma inesperada.");
	}else if(yychar == OTHER){
		print_resultado("Caractere(s) invalido(s) -> [%s", yytext);
	}else{
		print_resultado("Erro de sintaxe na coluna [%d]: %s", col, yytext);
	}
}

int main(int argc, char **argv)
{
	int flag = 0;
    while(flag != -1){
		int parser = yyparse();
		if(yychar == OTHER){
			int token = 0;
			while(token != EOL){
				if(token == OTHER){
					printf(",%s", yytext);
				}
                else if(token == END_OF_FILE){
					flag = -1;
					break;
				}
				token = yylex();
			}
			printf("]");
		}
        else if(parser != 0 && *yytext != '\n'){
			int token = 0;
			while(token != EOL){
				if(token == END_OF_FILE){
					flag = -1;
					break;
				}
				token = yylex();
			}
		}
		col = 0;
	}
    return 0;
}