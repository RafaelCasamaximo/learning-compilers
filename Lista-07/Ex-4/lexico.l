/* Nao usar a biblioteca do flex*/
%option noyywrap

%{

typedef struct properties{
	int total_lines;
	int blank_lines;
	int lines_with_comments;
	int non_blank_lines;
	int non_comments_lines;
	int semi_colons;
	int preprocessor_lines;
}Properties;

//Aux functions
int countChar(char* content, char id){
    int frequency = 0;
    for(int i = 0; i < strlen(content); i++){
        if(content[i] == id){
            frequency++;
        }
    }
    return frequency;
}

//Functions for each token
void preprocessorCounter(Properties *prop, char* yytext){
	prop->total_lines += 1;
	prop->preprocessor_lines += 1;
	prop->non_blank_lines += 1;
	prop->semi_colons += countChar(yytext, ';');
}

void blankLineCounter(Properties *prop, char* yytext){
	prop->total_lines += 1;
	prop->blank_lines += 1;
}

void commentCounter(Properties *prop, char* yytext){
	prop->total_lines += 1;
	prop->lines_with_comments += 1;
	prop->semi_colons += countChar(yytext, ';');
}

void blockCommentCounter(Properties *prop, char* yytext){
	prop->total_lines += countChar(yytext, '\n');
	prop->lines_with_comments += countChar(yytext, '\n');
	prop->semi_colons += countChar(yytext, ';');
}

void nonBlankLineCounter(Properties *prop, char* yytext){
	prop->total_lines += 1;
	prop->non_blank_lines += 1;
	prop->semi_colons += countChar(yytext, ';');
}

void sumProperties(Properties *src, Properties *dest){
	dest->total_lines += src->total_lines;
	dest->blank_lines += src->blank_lines;
	dest->lines_with_comments += src->lines_with_comments;
	dest->non_blank_lines += src->non_blank_lines;
	dest->non_comments_lines += src->non_comments_lines;
	dest->semi_colons += src->semi_colons;
	dest->preprocessor_lines += src->preprocessor_lines;
}

void resetProperties(Properties *prop){
	prop->total_lines = 1;
	prop->blank_lines = 0;
	prop->lines_with_comments = 0;
	prop->non_blank_lines = 0;
	prop->non_comments_lines = 0;
	prop->semi_colons = 0;
	prop->preprocessor_lines = 0;
}

	Properties arquivo;
	Properties total;

%}

%%

[\t\r\f]*("#include"|"#define").*\n								{preprocessorCounter(&arquivo, yytext);}
[\t\r\f]*[\n]													{blankLineCounter(&arquivo, yytext);}
[\t\r\f]*"//".*[\n]												{commentCounter(&arquivo, yytext);}
[\t\r\f]*("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/").*[\n]		{blockCommentCounter(&arquivo, yytext);}
.*[\n]															{nonBlankLineCounter(&arquivo, yytext);}

%%

int main(int argc, char **argv)
{
	resetProperties(&arquivo);
	resetProperties(&total);

	printf(" total    blank lines w/   nb, nc    semi- preproc. arquivo\n");
	printf(" lines    lines comments    lines   colons  direct.\n");
	printf("------+--------+--------+--------+--------+--------+----\n");
	
	for(int i=1;i<argc;i++){
		FILE* f = NULL;
		f = fopen(argv[i], "r");
		yyset_in(f);
		yylex();
		fclose(f);

		printf("%6d %8d %8d %8d %8d %8d %s\n", arquivo.total_lines, arquivo.blank_lines, arquivo.lines_with_comments, arquivo.non_blank_lines, arquivo.semi_colons, arquivo.preprocessor_lines, argv[i]);

		sumProperties(&arquivo, &total);
		resetProperties(&arquivo);
	}
	printf("%6d %8d %8d %8d %8d %8d total\n", total.total_lines, total.blank_lines, total.lines_with_comments, total.non_blank_lines, total.semi_colons, total.preprocessor_lines);
}
