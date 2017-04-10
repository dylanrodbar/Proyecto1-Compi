%{
#include "myscanner.h"
void yyerror(char *,char *, int);
int linea;
%}

%%

"auto"			  return KEYWORD;
"break"			  return KEYWORD;
"case"			  return KEYWORD;
"char"			  return KEYWORD;
"const"			  return KEYWORD;
"continue"	      return KEYWORD;
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

[0-9][0-9]*		  return INTEGER;

L?"/*"(\\.|[^\\"])*"*/"       		        return COMMENT;
"/*"((\*+[^/*])|([^*]))*\**"*/"             return COMMENT;
"/*"$*"*/"                		            return COMMENT;
"//".*$                  		            return COMMENT;
0[xX][a-fA-F0-9]+(u|U|l|L)*?	     		return CONSTANT; 
0[0-9]+(u|U|l|L)*?		     		        return CONSTANT; 
[0-9]+(u|U|l|L)*?		     		        return CONSTANT; 
L?'(\\.|[^\\'])+'	             		    return CONSTANT; 
[0-9]+[Ee][+-]?[0-9]+(f|F|l|L)?		 	    return CONSTANT; 
[0-9]*"."[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)?	return CONSTANT; 
[0-9]+"."[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)?	return CONSTANT; 

"{"                       return PUNTUACTOR;
"}"                       return PUNTUACTOR;
","                       return PUNTUACTOR;
"("                       return PUNTUACTOR;
")"                       return PUNTUACTOR;
"]"                       return PUNTUACTOR;
"["                       return PUNTUACTOR;
";"                       return PUNTUACTOR;
":"                       return PUNTUACTOR;

"~"                       return OPERATOR;
"?"                       return OPERATOR;
"^"                       return OPERATOR;
"+"			              return OPERATOR;	
"-"			              return OPERATOR;
"/"			              return OPERATOR;
"%"			              return OPERATOR;
"*"			              return OPERATOR;
"++"			          return OPERATOR;
"--"			          return OPERATOR;
"="			              return OPERATOR;
"<"			              return OPERATOR;
">"			              return OPERATOR;
"<="			          return OPERATOR;
"!="			          return OPERATOR;
"="			              return OPERATOR;
"+="			          return OPERATOR;
"-="			          return OPERATOR;
"*="			          return OPERATOR;
"/="			          return OPERATOR;
"%="			          return OPERATOR;
"!="			          return OPERATOR;
"."			              return OPERATOR;
"&"			              return OPERATOR;	
"|"			              return OPERATOR;
"->"			          return OPERATOR;
"&&"			          return OPERATOR;
"||"			          return OPERATOR;	
"..."			          return OPERATOR;
">>="			          return OPERATOR;
"<<="			          return OPERATOR;
"+="			          return OPERATOR;
"-="			          return OPERATOR;
"*="			          return OPERATOR;
"/="			          return OPERATOR;
"%="			          return OPERATOR;
"&="			          return OPERATOR;
"^="			          return OPERATOR;
"|="			          return OPERATOR;
">>"			          return OPERATOR;
"<<"			          return OPERATOR;

"#include"				  return INCLUDE;
"#define"				  return DEFINE;


[[:space:]]               return SPACE;

[a-zA-Z][_a-zA-Z0-9]*	  return IDENTIFIER;

L?\"(\\.|[^\\"]|\n)*\"    return LITERAL;
L?\'(\\.|[^\\"]|\n)*\'    return LITERAL;





                  
[ \t\n]
			  ;
.|[0-9]*[a-zA-Z][_a-zA-Z0-9]*   yyerror("Error léxico con \"%s\", en línea %i.\n",yytext,linea);


%%

int yywrap(void)
{
    return 1;
}



