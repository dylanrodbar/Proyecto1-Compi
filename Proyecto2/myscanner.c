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
char *color[]={"white","magenta","red","green", "purple","blue","orange"};
int numtokens[]={0,0,0,0,0,0,0};
int cantidad = 0; // es la cantidad total de tokens, como la suma de cada [i] de numtokens
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
    strcat(CodBeamer, "\\usepackage{pgfplots}\n"); 
    strcat(CodBeamer,"\\usetheme{Boadilla}\n \n \n");
    strcat(CodBeamer,"\\title{Analizador L\\'exico}\n");
    strcat(CodBeamer,"\\subtitle{Proyecto 1}\n");
    strcat(CodBeamer,"\\author{Ariana Berm\\'udez,Ximena Bola\\~nos, Dylan Rodr\\'iguez}\n");
    strcat(CodBeamer,"\\institute{Instituto Tecnol\\'ogico de Costa Rica}\n");
    strcat(CodBeamer,"\\date{\\today}\n");
    strcat(CodBeamer,"\\begin{document}\n");
    strcat(CodBeamer, "\\begin{frame}\n \\titlepage \n \\end{frame}");
    strcat(CodBeamer, "\\begin{frame}\n \\frametitle{An\\'alisis L\\'exico}\n \\end{frame}");
    strcat(CodBeamer, "\\begin{frame}\n \\frametitle{FLEX}\n Herramienta utilizada para realizar \\'escaneres. Este toma los valores de entrada y genera los tokens correspondientes.Seg\\'un la necesidad del programador. \\\\ Este genera un c\\'odigo fuente en C que se va a nombrar lex.yy.c en el cual se genera una funci\\'on yylex() la cu\\'al se encarga de analizar el c\\'odigo fuente. \\end{frame}");
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer,"\\frametitle{C\\'odigo Analizado}\n");	
}
void finalizarBeamer(void){
    strcat(CodBeamer,"\n\\end{frame}\n");
    strcat(CodBeamer,"\\end{document}\n");
    fputs(CodBeamer,beamer);
    fclose(beamer);
}
void CheckToken(char *text){
    if(strcmp(yytext, "{")==0)
      strcat(CodBeamer,"\\{");
    else{
	if(strcmp(yytext, "}")==0)
	      strcat(CodBeamer,"\\}");
	else{
	      strcat(CodBeamer,yytext);
	     }

		
        }
    
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
	CheckToken(yytext);
        strcat(CodBeamer,"} ");
	
	if(strcmp(yytext, ";") == 0 || strcmp(yytext, "{") == 0 || strcmp(yytext, "}") == 0){
          strcat(CodBeamer,"\\\\ \n ");
        }
	if(yylineno%10==0){
	  strcat(CodBeamer,"\\end{frame}\n");
	  strcat(CodBeamer,"\\begin{frame}\n");	
	}
    }
	
    generateHistogram(); 
    generatePieChart(); 
    finalizarBeamer();
    return 0;

}

void generateHistogram(){
    strcat(CodBeamer,"\\end{frame}\n");
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer,"\\frametitle{Histograma}\n"); 
    strcat(CodBeamer, "\\begin{tikzpicture}\n");
    strcat(CodBeamer, "\\begin{axis}[ybar interval, ymax=");
    cantidad = numtokens[1] + numtokens[2] + numtokens[3] + numtokens[4] + numtokens[5] + numtokens[6];
    char max[15];
    sprintf(max, "%d", cantidad);
    strcat(CodBeamer, max);
    strcat(CodBeamer, ", ymin=0, minor y tick num = 3]\n"); 
    strcat(CodBeamer, "\\addplot coordinates { "); 
    for(int i = 1; i < 7 ; i++){
        strcat(CodBeamer, "("); 
        char strI[15];
        sprintf(strI, "%d", i);
        strcat(CodBeamer, strI); 
        strcat(CodBeamer, " , ");
        char strICantidad[15];
        sprintf(strICantidad, "%d", numtokens[i]); 
        strcat(CodBeamer, strICantidad); 
        strcat(CodBeamer, ") "); 
    }
    strcat(CodBeamer, " (7, 0) "); 
    strcat(CodBeamer, "}; \n\\end{axis}\n"); 
    strcat(CodBeamer, "\\end{tikzpicture}\n");
    strcat(CodBeamer,"\\end{frame}\n");
    
}

void generatePieChart(){
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer,"\\frametitle{Histograma tipo Pastel}\n");
    strcat(CodBeamer, "\\def\\angle{0}\n");
    strcat(CodBeamer, "\\def\\radius{3}\n"); 
    strcat(CodBeamer, "\\def\\cyclelist{{\"yellow\",\"blue\",\"red\",\"green\"}}\n");
    strcat(CodBeamer, "\\newcount\\cyclecount \\cyclecount=-1\n");
    strcat(CodBeamer, "\\newcount\\ind \\ind=-1\n");
    strcat(CodBeamer, "\\begin{tikzpicture}[nodes = {font=\\sffamily}]\n");
    strcat(CodBeamer, "\\foreach \\percent/\\name in {\n");
    for(int i = 1; i < 7 ; i++){
     char strICantidad[15];
        char strIPercent[15];
        int percentage = numtokens[i] * 100 / cantidad; 
        sprintf(strIPercent, "%d", percentage); 
        strcat(CodBeamer, strIPercent); 
        strcat(CodBeamer, "/");
        identifierTokenType(i); 
        if (i == 6){
            strcat(CodBeamer, "\n");
        }
        else
            strcat(CodBeamer, ",\n");
        
    }
    strcat(CodBeamer, " } {\n"); 
    strcat(CodBeamer, "\\ifx\\percent\\empty\\else\n"); 
    strcat(CodBeamer, "\\global\\advance\\cyclecount by 1\n"); 
    strcat(CodBeamer, "\\global\\advance\\ind by 1\n"); 
    strcat(CodBeamer, "\\ifnum3<\\cyclecount\n"); 
    strcat(CodBeamer, "\\global\\cyclecount=0\n"); 
    strcat(CodBeamer, "\\global\\ind=0\n"); 
    strcat(CodBeamer, "\\fi\n"); 
    strcat(CodBeamer, "\\pgfmathparse{\\cyclelist[\\the\\ind]}\n"); 
    strcat(CodBeamer, "\\edef\\color{\\pgfmathresult}\n"); 
    strcat(CodBeamer, "\\draw[fill={\\color!50},draw={\\color}] (0,0) -- (\\angle:\\radius)\n"); 
    strcat(CodBeamer, "arc (\\angle:\\angle+\\percent*3.6:\\radius) -- cycle;\n"); 
    strcat(CodBeamer, "\\node at (\\angle+0.5*\\percent*3.6:0.7*\\radius) {\\percent\\,\\\%};\n"); 
    strcat(CodBeamer, "\\node[pin=\\angle+0.5*\\percent*3.6:\\name]\n"); 
    strcat(CodBeamer, "at (\\angle+0.5*\\percent*3.6:\\radius) {};\n"); 
    strcat(CodBeamer, "\\pgfmathparse{\\angle+\\percent*3.6}\n"); 
    strcat(CodBeamer, "\\xdef\\angle{\\pgfmathresult} \% and store in \\angle\n"); 
    strcat(CodBeamer, "\\fi\n"); 
    strcat(CodBeamer, "};\n"); 
 
    strcat(CodBeamer,"\\end{tikzpicture}\n");
}

void identifierTokenType(int i){
    switch(i){
        case 0:
            strcat(CodBeamer, "NULL"); 
            break; 
        case 1: 
            strcat(CodBeamer, "KEYWORD"); 
            break; 
        case 2: 
            strcat(CodBeamer, "INTEGER");
            break; 
        case 3: 
            strcat(CodBeamer, "IDENTIFIER"); 
            break; 
        case 4: 
            strcat(CodBeamer, "CONSTANT"); 
            break;
        case 5: 
            strcat(CodBeamer, "OPERATOR"); 
            break; 
        case 6: 
            strcat(CodBeamer, "PUNTUACTOR"); 
            break; 
    }
}
void yyerror(char *texto,char *simbolo, int linea){
     printf(texto,simbolo,linea);
     strcat(CodBeamer,"\\colorbox{red}{");
     strcat(CodBeamer, simbolo);
     strcat(CodBeamer,"}");

};
int main(void)
{
    scanner();
    
}


