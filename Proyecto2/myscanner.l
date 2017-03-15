%{
#include "myscanner.h"
%}

%%

[a-zA-Z][_a-zA-Z0-9]*	  return IDENTIFIER;
[1-9][0-9]*		  return INTEGER;
","                       return COMMA;
"("                       return LPAREN;
")"                       return RPAREN;
"{"                       return LCURLYBRACE;
"}"                       return RCURLYBRACE;
":"                       return COLON;
[ \t\n]			  ;
.			  printf("caracter inesperado\n");


%%

int yywrap(void)
{
    return 1;
}


