%{
/* Global and header definitions required */
#define YYSTYPE char *
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <alloca.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
char *progname; //this is used for the program name right here

int yydebug=1; 
char buffer[2048]; /* This is the buffer right here used for transfering the data */
int yylex (void);
void yyerror (char const *);

%}
/* Declarations (Optional token definitions) */
%token EQUALS POWER NUMBER LPAREN RPAREN COMMA POW PID INTEGER DOUBLE LBRACKET RBRACKET CREA RB LB RP LP
%left PLUS MINUS
%left TIMES DIVIDE

%%
/* Parsing ruleset definitions */

line :
/* Nothing */
|
line next {

};

something : something
{ 

	memset(buffer,0,0); //set the buffer back to zero

	fprintf(buffer,"%s + %s", $1, $2); //this is what we want to print out the information to the buffer

	strcpy($$,buffer); //do a string copy operation...



}
;
/* Below here add the stuff for the new shit*/



%%

/* Additional C source code */



int main(int argc, char **argv) 
{

	progname = argv[0];
	
	yyparse();
	
	//puts(buffer);
	return 0;

	
}


yyerror(char *s)
{

	fprintf( stderr ,"%s: %s\n" , progname , s );
}
