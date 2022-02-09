%option noyywrap
%{

#include <sintatico.tab.h>
#include<string.h>

int col = 0;

%}

%%

"+"         {col++; return ADD;}
"-"         {col++; return SUB;}
"*"         {col++; return MUL;}
"/"         {col++; return DIV;}
"^"         {col++; return POW;}
"%"         {col++; return MOD;}
"sen"       {col += 3; return SEN;}
"cos"       {col += 3; return COS;}
"tan"       {col += 3; return TAN;}
"abs"       {col += 3; return ABS;}
"("         {col++; return LPAREN;}
")"         {col++; return RPAREN;}

[0-9]+                      {col += strlen(yytext); return NUM;}
[0-9]+"."|[0-9]*"."[0-9]+   {col += strlen(yytext); return REAL;}
[a-z][a-z0-9]*              {col += strlen(yytext); return VAR;}

\n          {return EOL;}
[ \t]       {col++;}
.           {return OTHER;}
<<EOF>>     {return END_OF_FILE;}

%%