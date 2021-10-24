%option noyywrap

%%

"if"                {printf("IF");}
[a-z][a-z0-9]*      {printf("%s ID\n", yytext);}
[0-9]+              {printf("%s NUM\n", yytext);}
"."[0-9]+           {printf("%s REAL\n", yytext);}
[0-9]+"."[0-9]*     {printf("%s REAL\n", yytext);}
"--"[a-z]*[\n]      {fwrite(yytext, sizeof(char), strlen(yytext)-1, stdout); printf(" comment\n");}
" "|[\t]            {printf("white space\n");}
[\n]                {}
.                   {printf("%s error\n", yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
