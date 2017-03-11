%{
#include "myscanner.h"
%}

%%

"auto"			  return KEYWORD;
"break"			  return KEYWORD;
"case"			  return KEYWORD;
"char"			  return KEYWORD;
"const"			  return KEYWORD;
"continue"	          return KEYWORD;
"default"		  return KEYWORD;
"do"			  return KEYWORD;
"double"		  return KEYWORD;
"else"			  return KEYWORD;
"enum"			  return KEYWORD;
"extern"		  return KEYWORD;
"float"			  return KEYWORD;
"for"			  return KEYWORD;
"goto"			  return KEYWORD;
"if"			  return KEYWORD;
"int"			  return KEYWORD;
"long"			  return KEYWORD;
"register"		  return KEYWORD;
"return"		  return KEYWORD;
"short"			  return KEYWORD;
"signed"		  return KEYWORD;
"sizeof"		  return KEYWORD;
"static"		  return KEYWORD;
"struct"		  return KEYWORD;
"switch"		  return KEYWORD;
"typedef"		  return KEYWORD;
"union"			  return KEYWORD;
"unsigned"		  return KEYWORD;
"void"			  return KEYWORD;
"volatile"		  return KEYWORD;
"while"			  return KEYWORD;

"/*"[a-zA-Z]*[_a-zA-Z0-9]*"*/"* return CONSTANT;
"//"[a-zA-Z]*[_a-zA-Z0-9]*     return CONSTANT;


"{"                       return PUNTUACTOR;
"}"                       return PUNTUACTOR;
","                       return PUNTUACTOR;
"("                       return PUNTUACTOR;
")"                       return PUNTUACTOR;
";"                       return PUNTUACTOR;



"+"			  return OPERATOR;	
"-"			  return OPERATOR;
"/"			  return OPERATOR;
"%"			  return OPERATOR;
"*"			  return OPERATOR;
"++"			  return OPERATOR;
"--"			  return OPERATOR;
"="			  return OPERATOR;
"<"			  return OPERATOR;
">"			  return OPERATOR;
"<="			  return OPERATOR;
"!="			  return OPERATOR;
"="			  return OPERATOR;
"+="			  return OPERATOR;
"-="			  return OPERATOR;
"*="			  return OPERATOR;
"/="			  return OPERATOR;
"%="			  return OPERATOR;
"!="			  return OPERATOR;	

[a-zA-Z][_a-zA-Z0-9]*	  return IDENTIFIER;
[0-9][0-9]*		  return INTEGER;


                  
[ \t\n]			  ;
.			  printf("Caracter inesperado.\n");


%%

int yywrap(void)
{
    return 1;
}


