%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>
#include "mainyacc.tab.h"
extern YYSTYPE yylval;

%}
%%


%option noyywrap

%%




[0-9]+	{	
	printf("number\n"); 
	
	} 

[0-9]+.[0-9]+ {	
	printf("decimal\n"); 
	
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
	
	
