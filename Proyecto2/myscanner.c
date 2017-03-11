#include <stdio.h>
#include <stdbool.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] ={NULL,"auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if","int","long",
"register","return","short","signed","sizeof","static","struct",
"switch","typedef","union","unsigned","void","volatile","while"};
/*
FILE *file;

void leerArchivo(void){
    printf("Ruta del archivo: \n");
    char NombreArchivo[150];
    gets(NombreArchivo);
    file = fopen(NombreArchivo, "r");
}



/*Función que indica si se leyó o no correctamente el archivo
bool seLeyoArchivo(void){
    if (file) {
        return true;

    }else{
    return false;
    }

}

/*Función que se encarga de cerrar el archivo
void cerrarArchivo(void){
    fclose(file);
}
*/

int nextToken(void)
{
    return yylex();
}

void preprocess(void)
{
    
}

int scanner(void)
{
    int ntoken, vtoken;
    
    ntoken = nextToken();
    while(ntoken) {
        printf("%d\n", ntoken);
        ntoken = nextToken();
    }
    
    return 0;

}

int main(void)
{
    scanner();
    
}


