%{
#define YYSTYPE double
#include <stdio.h>
#include <string.h>



%}
%option noyywrap

%%




[0-9]+	{	
	printf("number\n"); 
		return NUM;
	} 

[0-9]+.[0-9]+ {	
	printf("decimal\n"); 
	return NUM;
	} 

"pid:"	{
	printf("PID!\n"); 
	
	}
	
"["		{
	printf("Left Bracket!\n"); 
	
	}
	
"]"		{
	printf("RIGHT BRACKET!\n"); 
	
	}
.|'\n' 		{
	printf("ERROR"); 
	
	}
	

"++" return INC;
"--" return DEC;
"+" return PLUS;
"-" return MINUS;
"~" return UNARYMINUS;
"/" return DIV;
"*" return MUL;
"^" return POW;
"!" return FACT;
"(" return OPENBRACKET;
")" return CLOSEBRACKET;
"%" return MOD;
"^^" return XOR;
"!!" return NOT;
"\n" return EOLN;

%%


int main(void)
{
    /* Call the lexer, then quit. */
    yylex();
    return 0;
}


	

