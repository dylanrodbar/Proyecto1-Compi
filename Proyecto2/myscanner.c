#include <stdio.h>
#include <stdbool.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
FILE *beamer;
char *names[] ={NULL,"auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if","int","long",
"register","return","short","signed","sizeof","static","struct",
"switch","typedef","union","unsigned","void","volatile","while"};
char *color[]={"white","blue","red","green", "yellow","pink","purple"};
int numtokens[]={0,0,0,0,0,0,0};
FILE *file;

char *CodBeamer[5000000];
void leerArchivo(void){
    printf("Ruta del archivo: \n");
    char NombreArchivo[150];
    gets(NombreArchivo);
    file = fopen(NombreArchivo, "r");
}



/*Función que indica si se leyó o no correctamente el archivo*/
bool seLeyoArchivo(void){
    if (file) {
        return true;

    }else{
    return false;
    }

}

/*Función que se encarga de cerrar el archivo*/
void cerrarArchivo(void){
    fclose(file);
}

int nextToken(void)
{
    return yylex();
}

void preprocess(void)
{
    
}


void inicializarBeamer(void){
    beamer=fopen("main.tex", "w");
    strcat(CodBeamer,"\\documentclass{beamer}\n");
    strcat(CodBeamer,"\\usetheme{Boadilla}\n \n \n");
    strcat(CodBeamer,"\\title{Analizador Lexico}\n");
    strcat(CodBeamer,"\\subtitle{Proyecto 1}\n");
    strcat(CodBeamer,"\\author{Ariana Bermudez,Ximena Bolanos, Dylan Rodriguez}\n");
    strcat(CodBeamer,"\\institute{Instituto Tecnologico de Costa Rica}\n");
    strcat(CodBeamer,"\\date{\\today}\n");
    strcat(CodBeamer,"\\begin{document}\n");
    strcat(CodBeamer,"\\begin{frame}\n");
}
void finalizarBeamer(void){
    strcat(CodBeamer,"\n\\end{frame}\n");
    strcat(CodBeamer,"\\end{document}\n");
    fputs(CodBeamer,beamer);
    fclose(beamer);
}
int scanner(void)
{
    int ntoken, vtoken;
    inicializarBeamer();
    ntoken = nextToken();
    
    while(ntoken) {
        printf("%d\n", ntoken);
        numtokens[ntoken]++;
        ntoken = nextToken();
	strcat(CodBeamer,"\\textcolor{");
	strcat(CodBeamer,color[ntoken]);
	strcat(CodBeamer,"}{");	
	strcat(CodBeamer,yytext);
        strcat(CodBeamer,"} ");
	if(yylineno%10==0){
	  strcat(CodBeamer,"\\end{frame}\n");
	  strcat(CodBeamer,"\\begin{frame}\n");	
	}
    }
    finalizarBeamer();
    return 0;

}

int main(void)
{
    scanner();
    
}


