#include <stdio.h>
#include <stdbool.h>
#include "myscanner.h"
#include "estructuras.h"
#include <string.h>
#include <stdlib.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

char *includes[] = {};

struct defineS defines[]; 
int numIncludes = -1; //contador de los includes que se tendrán en el array de chars includes

int numDefines = -1;  //contador de los defines que se tendrán en el array de structs defines
FILE *tmpFile;

FILE *beamer;
char *names[] ={NULL,"auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if","int","long",
"register","return","short","signed","sizeof","static","struct",
"switch","typedef","union","unsigned","void","volatile","while"};
char *color[]={"white","magenta","red","green", "purple","blue","orange","pink"};
int numtokens[]={0,0,0,0,0,0,0,0};
int cantidad = 0; // es la cantidad total de tokens, como la suma de cada [i] de numtokens
FILE *file;

char *CodBeamer[5000000];





FILE * leerArchivo(void){
    //printf("Ruta del archivo: \n");
    //char NombreArchivo[150];
    //gets(NombreArchivo);
    FILE *file;    //Es el archivo de entrada del preprocesador
    file = fopen("hola.c", "r");
    return file;
} 



/*Función que indica si se leyó o no correctamente el archivo*/
bool seLeyoArchivo(FILE *file){
    if (file) {
        return true;

    }else{
    return false;
    }

}

/*Función que se encarga de cerrar el archivo*/
void cerrarArchivo(FILE *file){
    fclose(file);
}



int nextToken(void)
{   
    return yylex();
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
    addExplanation(); 
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer,"\\frametitle{C\\'odigo Analizado}\n");	
}

void addExplanation(){
    strcat(CodBeamer, "\\begin{frame}\n \\frametitle{An\\'alisis L\\'exico}\n Se hizo un analizador l\\'exico con la ayuda de la herramienta Flex, para el lenguaje C y que corre en C, este analizador encuentra los tokens y busca su tipo, e incrementa el contador de ese tipo para luego generar histogramas y gr\\'aficos de pastel. Estos gr\\'aficos son mostrados en una presentaci\\'on de beamer, que ser\\'a tambi\\'en la salida del Scanner. En la presentaci\\'on se definieron los \\colorbox{red}{errores} con un subrayado rojo,y para los token se defini\\'o:\\begin{itemize} \\item magenta para los \\textcolor{magenta} {KEYWORD}  \\item rojo para los \\textcolor{red}{INTEGER} \\item verde para los \\textcolor{green} {IDENTIFIER} \\item morado para los \\textcolor{purple}{CONSTANT} \\item azul para los \\textcolor{blue} {OPERATOR} \\item naranja para los \\textcolor{orange} {PUNTUACTOR} \\item rosado para los \\textcolor{pink} {LITERAL} \\end{itemize} \\end{frame}");
    strcat(CodBeamer, "\\begin{frame}\n \\frametitle{FLEX}\n Herramienta utilizada para realizar esc\\'aneres. Este toma los valores de entrada y genera los tokens correspondientes.Seg\\'un la necesidad del programador. \\\\ Este genera un c\\'odigo fuente en C que se va a nombrar lex.yy.c en el cual se genera una funci\\'on yylex() la cu\\'al se encarga de analizar el c\\'odigo fuente. Busca la librer\\'ia –lfl después de ser compilado y se enlaza con ella, para dar como resultado un ejecutable. \\\\ \n ");
    strcat(CodBeamer, "El fichero de entrada de flex tiene 3 secciones, y tiene que verse como:\\\\ \n ");

    strcat(CodBeamer, "\\textcolor{blue}{definiciones \\\\ \\\%\\\% \\\\ reglas \\\\ \\\%\\\% \\\\\ c\\'odigo de usuario} \\\\ \n");
    strcat(CodBeamer,"\\end{frame}\n");
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer, "Las definiciones contienen las declaraciones de nombres, y condiciones de arranque. Un ejemplo de nuestro programa es: \\newline \n"); 
    strcat(CodBeamer, "\\textcolor{red}{[a-zA-Z][\\_a-zA-Z0-9]*   return IDENTIFIER; \\newline [0-9][0-9]*    return INTEGER;} \\newline \n"); 
    strcat(CodBeamer, "Luego de definir estos campos se procede a explicar como funciona flex, el flex asocia las entradas, \\textbf{?`pero c\\'omo lo hace?}\\newline \n");
    strcat(CodBeamer, "El esc\\'aner analiza poco a poco las cadenas hasta que concuerden con alg\\'un patr\\'on propuesto por el programador. Si se puede emparejar m\\'as de una forma entonces tiene prioridad quien pueda asociar m\\'as texto y si en ese caso tambi\\'en son iguales entonces se elige por medio de quien est\\'e antes en el fichero de entrada.\\newline \nEl token tendr\\'a asociado el puntero a caracter global \\textbf{yytext}, y la longitud en la variable global entera \\textbf{yyleng}. Si no hay forma de asociarlo, se usa la regla por defecto. \\newline \n");  
    strcat(CodBeamer,"\\end{frame}\n");
    strcat(CodBeamer,"\\begin{frame}\n\\frametitle{FLEX - continuaci\\'on} \n");
    strcat(CodBeamer, "\\textbf{Acciones} \\newline \n"); 
    strcat(CodBeamer, "Todo patr\\'on tiene una acci\\'on asociada. Existen varias acciones, por ejemplo: si se pone \\newline \n"); 
    strcat(CodBeamer, "\\begin{table}[]\n\\centering\n\\caption{Acciones}\n\\label{Acciones}\n\\begin{tabular}{|l|l|}\n \\hline \n"); 
    strcat(CodBeamer, "\\\%\\\% \"texto\" & Har\\'a que se borren todas sus aparciones en la entrada. \\\\ \\hline \n");
    strcat(CodBeamer, "\\{ & \\begin{tabular}[c]{@{}l@{}}Tomar\\'a todo eso como parte de la acci\\'on hasta \\\\ que encuentre la llave que lo cierra, \\}.\\end{tabular} \\\\ \\hline \n");
    strcat(CodBeamer, "| & Hace que la acci\\'on actual aplique tambi\\'en para la siguiente. \\\\ \\hline  \n");
    strcat(CodBeamer, "\\end{tabular} \n\\end{table} \n");  
    strcat(CodBeamer, "El yylex() es una funci\\'on que procesa tokens desde donde lo dejaron la \\'ultima vez. Directivas especiales que se pueden incluir dentro de una acci\\'on"); 
    //strcat(CodBeamer, ""); 
    strcat(CodBeamer, "\\end{frame}\n"); 

        strcat(CodBeamer,"\\begin{frame}\n\\frametitle{FLEX - continuaci\\'on} \n");
    strcat(CodBeamer, "\\textbf{Acciones} \\newline \n"); 
    strcat(CodBeamer,"Las acciones puede modificar los yytext exepto su largo, para ello se le puede agregar un \\%array y as\\'i modificar totalmente la variable yytext, que es donde se guarda el valor del token actual.\\\\");
    strcat(CodBeamer,"Directivas especiales:\\begin{itemize} \\item ECHO: copia yytext a la salida del esc\\'aner  \\item BEGIN: pone al esc\\'aner en la codici\\'on de arranque correspondiente. \\item REJECT: ordena a proceder con al \"segunda mejor regla.\" \\item yymore(): despues de emparejar una regla el valor de yytext actual debe se reemplazado por el siguiente.\\end{itemize}");
	
    strcat(CodBeamer, "\\end{frame}\n"); 

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
    cantidad = numtokens[1] + numtokens[2] + numtokens[3] + numtokens[4] + numtokens[5] + numtokens[6]+ numtokens[7];
    char max[15];
    sprintf(max, "%d", cantidad);
    strcat(CodBeamer, max);
    strcat(CodBeamer, ", ymin=0, minor y tick num = 3]\n"); 
    strcat(CodBeamer, "\\addplot coordinates { "); 
    for(int i = 1; i < 8 ; i++){
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
    strcat(CodBeamer, " (8, 0) "); 
    strcat(CodBeamer, "}; \n\\end{axis}\n"); 
    strcat(CodBeamer, "\\end{tikzpicture}\n");
    strcat(CodBeamer,"\\end{frame}\n");
    
}

void generatePieChart(){
    strcat(CodBeamer,"\\begin{frame}\n");
    strcat(CodBeamer,"\\frametitle{Histograma tipo Pastel}\n");
    strcat(CodBeamer, "\\def\\angle{0}\n");
    strcat(CodBeamer, "\\def\\radius{3}\n"); 
    strcat(CodBeamer, "\\def\\cyclelist{{\"yellow\",\"blue\",\"red\",\"green\",\"orange\",\"purple\"}}\n");
    strcat(CodBeamer, "\\newcount\\cyclecount \\cyclecount=-1\n");
    strcat(CodBeamer, "\\newcount\\ind \\ind=-1\n");
    strcat(CodBeamer, "\\begin{tikzpicture}[nodes = {font=\\sffamily}]\n");
    strcat(CodBeamer, "\\foreach \\percent/\\name in {\n");
    for(int i = 1; i < 8 ; i++){
     char strICantidad[15];
        char strIPercent[15];
        int percentage = numtokens[i] * 100 / cantidad; 
        sprintf(strIPercent, "%d", percentage); 
        strcat(CodBeamer, strIPercent); 
        strcat(CodBeamer, "/");
        identifierTokenType(i); 
        if (i == 7){
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
	case 7: 
            strcat(CodBeamer, "LITERAL"); 
            break; 
    }
}
void yyerror(char *texto,char *simbolo, int linea){
     printf(texto,simbolo,linea);
     strcat(CodBeamer,"\\colorbox{red}{");
     strcat(CodBeamer, simbolo);
     strcat(CodBeamer,"}");

};




/*Función encargada de evaluar si ya existe una librería de inclusión en la tabla de inclusiones*/
bool existeInclude(char include[25])
{
    for(int i = 0; i<numIncludes; i++)
    {
        if(strcmp(includes[i], include) == 0)
        {
            return true;
        }

    }
    
    return false;

}


/*Función encargada de evaluar si ya existe un define en la tabla de definiciones*/
int existeDefine(char define[25])
{
    for(int m = 0; m<=numDefines; m++)
    {
        if(strcmp(defines[m].palabra, define) == 0)
        {
            return m;
        }

    }
    
    return -1;

}



/*Función encargada de retornar el valor de un define específico tomado de la tabla de definiciones*/

char *valorDefine(char *palabra)
{
    int ex = existeDefine(palabra);
    if(ex == -1)
    {
        return palabra;
    }

    else
    { 
        return valorDefine(defines[ex].vDefine);
    }
    
}



/*Función encargada de buscar los #include o #define y manejarlos*/
void preprocess(FILE *file)
{
    int in_char;
 
    char palabra[25] = "";
    char vDefine[300] = "";
    char tipo[7] = "";
    
    
    int j = 0; //contador para tipo
    int i = 0; //contador para palabra
    int a = 0; //contador para vDefine
    
    while ((in_char = getc(file)) != EOF)
    {
        //Se se encuentra un #, se toman los valores correspondientes seguidos de dicho símbolo
        if (in_char == '#')
        {
            
            in_char = getc(file);
            //Se llena tipo, el cual puede tomar el valor de include o define
            while (!isspace(in_char))
            {
                  tipo[j] = in_char;
                  j++;
                  in_char = getc(file);
            }
            
            in_char = getc(file);

            //Se toma el valor después del include o define
            while (!isspace(in_char))
            {
                  if(in_char != '"')
                  {
                      palabra[i] = in_char;
                      i++;
                  }

                  in_char = getc(file);
                  
            }
            

            //Si tipo es include
            if(strcmp(tipo, "include") == 0)
            {
                
                    
		/*Se evalúa si ya existe el include en la tabla de includes
                Si ya existe, se notificará*/
		if(existeInclude(palabra))
		{
		    printf("Inclusión duplicada de librería %s", palabra);
		}

		/*En caso contrario, se seguirán leyendo librerías*/
		else
		{
		        
		    numIncludes++;
                    
                    includes[numIncludes] = (char *)malloc(sizeof(char));                
                    strcpy(includes[numIncludes], palabra);
		    FILE *n = fopen(palabra, "r");
		    preprocess(n);
		}
            }
            
            /*Se encuentra un define*/
            else if(strcmp(tipo, "define") == 0)
            {
             
                 in_char = getc(file);
                 /*Se busca el valor asignado al identificador del define*/
                 
		
                 while (!isspace(in_char))
                 {
                      vDefine[a] = in_char;
                      a++;
                      in_char = getc(file);
                  
                 }
                 
                 printf("%s\n", vDefine);


                 numDefines++;
                 
                 
                 int ex = existeDefine(palabra); 
                 
                 /*Si la palabra no existe en la tabla de defines, se agregará el nuevo elemento*/
                 if(ex == -1)
                 {

                     
                     
                     
                     strcpy(defines[numDefines].palabra, palabra);
                     
                     
                     
                     strcpy(defines[numDefines].vDefine, vDefine);
                     
                                          
                     
                   
                     printf("%s\n", defines[0].palabra);
                     printf("%s\n", defines[0].vDefine);
                     
                     
                    
                     
                 }
                 
                 /*Si la palabra existe en la tabla de defines, se cambiará el valor del elemento por el nuevo encontrado*/
                 else
                 {   
                     strcpy(defines[ex].vDefine, vDefine);
                     numDefines--;
                 }  
                                   

            }
            
            
        }
        else
        {
            
            //char palabra1[25] = "";
            //printf("holiiiiiiiiiiiiiiiiiiiii");
            while (!isspace(in_char))
            {

                  palabra[i] = in_char;
                  i++;
                  in_char = getc(file);
            
            }
            
            
            
            int existe = existeDefine(palabra); 
            if(existe == -1)
            {
                fputs(palabra, tmpFile);
                
            }
            else  
            {
                char *p = valorDefine(defines[existe].vDefine); 
                fputs(p, tmpFile);
            }
            fputc(in_char, tmpFile);
            
             
        }
        
        a=0;
        j=0;
        i=0;
        memset(&palabra[0], 0, sizeof(palabra));
        memset(&tipo[0], 0, sizeof(tipo));
        memset(&vDefine[0], 0, sizeof(vDefine));
        
        
        
    }
                       
    
}


int main(void)
{
    
    FILE *f = leerArchivo();
    if(seLeyoArchivo(f))
    {
        printf("Se pudo leer el archivo correctamente");
        tmpFile = fopen("config.c", "wt");
        preprocess(f);
        fclose(tmpFile);
    }
    else
    {
        printf("No se pudo leer el archivo correctamente");
    }    
    
    scanner();
    //system("pdflatex main.tex");
    return 0; 
}


