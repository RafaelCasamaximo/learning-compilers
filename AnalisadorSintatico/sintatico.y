%{
#include<stdio.h>
#include<string.h>

extern int yylex();
extern char* yytext;
void yyerror(char *s);

extern int total_lines;
extern int total_chars;
FILE* inputFile = NULL;

void printPosFinder(FILE* auxFile, int aux){

	int i = 1;
	char character;

	fseek(auxFile, 0, SEEK_SET);

	while(i < aux)
	{
		character = fgetc(auxFile);
		if(character == '\n'){ 
            i++; 
        }
		if(character == EOF){ 
            break; 
        }
	}

	character = fgetc(auxFile);
	while(character != '\n' && character != EOF)
	{
		printf("%c", character);
		character = fgetc(auxFile);
	}
	printf("\n");
}

%}

	/*Estruturas*/
%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK		// Não Utilizado
%token SWITCH		// Não Utilizado
%token CASE			// Não Utilizado
%token DEFAULT		// Não Utilizado
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF 		// Não Utilizado
%token STRUCT 		// Não Utilizado

	/*Operadores Matemático*/
%token ADD
%token SUB
%token MULT
%token DIV
%token MOD
%token INC
%token DEC

	/*Bitwise*/
%token BIT_AND
%token BIT_OR
%token BIT_NOT
%token BIT_XOR

	/*Logicos*/
%token LOG_AND
%token LOG_OR
%token LOG_NOT
%token EQUALS
%token NOT_EQUALS
%token LESS
%token GREAT
%token LEQ
%token GEQ

	/*Shift*/
%token RSHIFT
%token LSHIFT

	/*Assign*/
%token ASSIGN
%token ADD_ASSIGN
%token SUB_ASSIGN

	/*Delimitadores*/
%token SEMICOLON
%token COMMA
%token COLON
%token LPAREN
%token RPAREN
%token LCBRACK
%token RCBRACK
%token LBRACK
%token RBRACK
%token QUEST_MARK
%token NUMBER_SIGN
%token POINTER_DEFERENCE // Não Utilizado

	/*Funções*/
%token DEFINE_T
%token PRINTF_T
%token SCANF_T
%token EXIT_T

	/*Variáveis*/
%token NUM_HEXA
%token NUM_OCTA
%token NUM_INT
%token CHARACTER
%token STRING
%token IDENTIFIER

	/*Comentarios*/
%token LINE_COMMENT 			// Não Utilizado
%token BLOCK_COMMENT 			// Não Utilizado
%token UNTERMINATED_COMMENT 	// Não Utilizado
%token OTHER 					// Não Utilizado
%token END_OF_FILE

%start programa

%%

programa: prog programa END_OF_FILE																									{printf("SUCCESSFUL COMPILATION."); return 0;}
		| prog END_OF_FILE		    																								{printf("SUCCESSFUL COMPILATION."); return 0;}
;

prog: declaration {}
    | function     {}
;

declaration: NUMBER_SIGN DEFINE_T IDENTIFIER expression  																			{}
          | var_declaration                              																			{}
          | prot_declaration                             																			{}
;

function: type pointer IDENTIFIER parameters LCBRACK function_var_declaration commands RCBRACK										{}
;

function_var_declaration: var_declaration function_var_declaration																	{}
		   |              				    																						{}
;

var_declaration: type dec_var SEMICOLON 																							{}
;

dec_var: pointer IDENTIFIER array ASSIGN assignment dec_var_aux 																	{}
       | pointer IDENTIFIER array dec_var_aux       																				{}
;

dec_var_aux: COMMA dec_var 																											{}
           |               																											{}
;

prot_declaration: type pointer IDENTIFIER parameters SEMICOLON																		{}
;

parameters: LPAREN param RPAREN																										{}
;

param: type pointer IDENTIFIER array param_aux																						{}
	 |	                                        																					{}
;

param_aux: COMMA param																												{}
		 |         																													{}
;

array: LBRACK expression RBRACK array																								{}
	 |              																												{}
;

type: INT																															{}
	| CHAR																															{}
	| VOID																															{}
;

block: LCBRACK commands RCBRACK	{}
;

commands: lista_comandos commands	{}
		| lista_comandos			{}
;

lista_comandos: DO block WHILE LPAREN expression RPAREN SEMICOLON	                                								{}
			  | IF LPAREN expression RPAREN block else_exp				                                							{}
			  | WHILE LPAREN expression RPAREN block					                                							{}
			  | FOR LPAREN optional_expression SEMICOLON optional_expression SEMICOLON optional_expression RPAREN block				{}
			  | PRINTF_T LPAREN STRING printf_exp RPAREN SEMICOLON		                                							{}
			  | SCANF_T LPAREN STRING COMMA BIT_AND IDENTIFIER RPAREN SEMICOLON		                								{}
			  | EXIT_T LPAREN expression RPAREN SEMICOLON				                                							{}
			  | RETURN optional_expression SEMICOLON								                            					{}
			  | expression SEMICOLON										                                						{}
			  | SEMICOLON												                                							{}
			  | block													                                							{}
;

printf_exp: COMMA expression																										{}
		  |             																											{}
;

else_exp: ELSE block																												{}
		|               																											{}
;

optional_expression: expression																										{}
	   		|            																											{}
;

expression: assignment                 																								{}
         | assignment COMMA expression 																								{}
;

assignment: exp_cond                         																						{}
          | unary_expression ASSIGN assignment     																					{}
          | unary_expression ADD_ASSIGN assignment 																					{}
          | unary_expression SUB_ASSIGN assignment 																					{}
;

exp_cond: exp_or_log                                     																			{}
        | exp_or_log QUEST_MARK expression COLON exp_cond 																			{}
;

exp_or_log: exp_and_log                  																							{}
        | exp_and_log LOG_OR exp_and_log 																							{}
;

exp_and_log: exp_or                 																								{}
           | exp_or LOG_AND exp_or  																								{}
;

exp_or: exp_xor                																										{}
      | exp_xor BIT_OR exp_xor 																										{}
;

exp_xor: exp_and                 																									{}
       | exp_and BIT_XOR exp_and 																									{}
;

exp_and: exp_equals                         																						{}
       | exp_equals BIT_AND exp_equals 																								{}
;

exp_equals: exp_relational                           																				{}
             | exp_relational EQUALS exp_relational     																			{}
             | exp_relational NOT_EQUALS exp_relational 																			{}
;

exp_relational: exp_shift					    																					{}
		      | exp_shift LESS exp_relational   																					{}
		      | exp_shift LEQ exp_relational																						{}
		      | exp_shift GEQ exp_relational																						{}
		      | exp_shift GREAT exp_relational																						{}
;

exp_shift: exp_add																													{}
		 | exp_add LSHIFT exp_shift																									{}
		 | exp_add RSHIFT exp_shift																									{}
;

exp_add: exp_mult																													{}
	   | exp_mult ADD exp_add																										{}
	   | exp_mult SUB exp_add																										{}
;

exp_mult: exp_cast																													{}
		| exp_cast MULT exp_mult																									{}
		| exp_cast DIV exp_mult																										{}
		| exp_cast MOD exp_mult																										{}
;

exp_cast: unary_expression																											{}
		| LPAREN type pointer RPAREN exp_cast																						{}
;

unary_expression: exp_postfix																										{}
		  | INC unary_expression																									{}
		  | DEC unary_expression																									{}
		  | BIT_AND exp_cast																										{}
		  | MULT exp_cast																											{}
		  | ADD exp_cast																											{}
		  | SUB exp_cast																											{}
		  | BIT_NOT exp_cast																										{}
		  | LOG_NOT exp_cast																										{}
;

exp_postfix: exp_prim				                            																	{}
		   | exp_postfix INC		                            																	{}
		   | exp_postfix DEC		                            																	{}
		   | exp_postfix LBRACK expression RBRACK			    																	{}
		   | exp_postfix LPAREN RPAREN						    																	{}
		   | exp_postfix LPAREN assignment exp_pf_aux RPAREN																		{}
;

exp_pf_aux: COMMA assignment exp_pf_aux																								{}
		  |       					    																							{}
;

exp_prim: IDENTIFIER	            																								{}
		| num               																										{}
		| CHARACTER		            																								{}
		| STRING		            																								{}
		| LPAREN expression RPAREN																									{}
;

num: NUM_INT																														{}
   | NUM_HEXA																														{}
   | NUM_OCTA																														{}
;

pointer: MULT 																														{}
       |          																													{}
;

%%

void yyerror(char *s)
{
	int i;

	switch(yychar){

		case UNTERMINATED_COMMENT:
			printf("error:lexical:%d:%d: unterminated comment", total_lines, total_chars);
			break;


		case OTHER:
			total_chars -= strlen(yytext);
			printf("error:lexical:%d:%d: %s", total_lines, total_chars, yytext);
			break;


		case END_OF_FILE:
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", total_lines, total_chars);
			printPosFinder(inputFile, total_lines);

            i = 1;
			while(i < total_chars)
			{ 
                printf(" "); 
				i++;
            }

			printf("^");
			break;

		default:
			total_chars -= strlen(yytext);
			printf("error:syntax:%d:%d: %s\n", total_lines, total_chars, yytext);
			printPosFinder(inputFile, total_lines);

            i = 1;
			while(i < total_chars)
			{ 
                printf(" "); 
				 i++;
            }

			printf("^");
			break;


	}
}

int main(int argc, char **argv)
{
	inputFile = stdin;
	yyparse();
    return 0;
}
