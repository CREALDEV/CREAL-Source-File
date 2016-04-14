%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>
#include "mainyacc.tab.h"
extern YYSTYPE yylval;

%}
%%




[0-9]				 {	yylval=strdup(yytext); return INTEGER;} 
[0-9].[0-9] 		 {	yylval=strdup(yytext); return DOUBLE;} 
"+"                  { return PLUS;       }
"-"                  { return MINUS;      }
"*"                  { return TIMES;      }
"/"                  { return DIVIDE;      }
"("                  { return LPAREN;     }
")"                  { return RPAREN;     }
","                  { return COMMA;      }
"^"					 {return POW;}
"pid:"				 {return PID;}
"["					 {return LBRACKET;     }
"]"					 {return RBRACKET;     }
"="					 {yyerror("Sorry this is not and equation, its an expression!!");}
[\n\t\r]				



%%


	

