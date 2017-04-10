#include <stdio.h>
#include <stdbool.h>
#include "myscanner.h"
#include "estructuras.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern int linea=1;
bool changeline=false;

/*
    Estas son las variables que serán accesibles durante todo el preprocesador
*/

/*****************************************************/
char *includes[] = {};     //Tabla con las cadenas que representarán a los includes que se encuentren en el programa
struct defineS defines[100] = {};  //Tabla con las cadenas que representarán a los includes que se encuentren en el programa
int numIncludes = -1;      //Contador de los includes que se tendrán en el array de cadenas includes
int numDefines = -1;       //Contador de los defines que se tendrán en el array de structs defines
bool error  = false;       //Booleano que indica cuando se encuentra un error en el programa
bool preproceso = false;
FILE *tmpFile;             //Archivo temporal que representa a la entrada para el scanner
/*****************************************************/

FILE *beamer;
char *names[] ={NULL,"auto","break","case","char","const","continue","default","do",
"double","else","enum","extern","float","for","goto","if","int","long",
"register","return","short","signed","sizeof","static","struct",
"switch","typedef","union","unsigned","void","volatile","while"};
char *color[]={"white","magenta","red","green", "purple","blue","orange","pink"};
int numtokens[]={0,0,0,0,0,0,0,0};
float percentTokens[]={0,0,0,0,0,0,0,0};
int cantidad = 0; // es la cantidad total de tokens, como la suma de cada [i] de numtokens
FILE *file;

char *CodBeamer[5000000];



FILE *leerArchivo(char NombreArchivo[]){
    FILE *file;    //Es el archivo de entrada del preprocesador
    file = fopen(NombreArchivo, "r");
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
    memset(&CodBeamer[0], 0, sizeof(CodBeamer));
    strcat(CodBeamer,"\\documentclass{beamer}\n");
    strcat(CodBeamer, "\\usepackage{pgfplots}\n"); 
    //strcat(CodBeamer, "\\usepackage[light]{antpolt}\n");
    //strcat(CodBeamer, "\\usepackage[T1]{fontenc}\n");    
    strcat(CodBeamer,"\\usetheme{progressbar}\n \n \n");
    strcat(CodBeamer,"\\usecolortheme{crane}\n \n \n");
    strcat(CodBeamer,"\\setbeamercolor{frametitle}{fg=brown}\n \n \n");
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
    strcat(CodBeamer, "\\begin{table}[]\n"); 
    strcat(CodBeamer, "\\centering\n"); 
    strcat(CodBeamer, "\\caption{Acciones}\n"); 
    strcat(CodBeamer, "\\label{Acciones}\n"); 
    strcat(CodBeamer, "\\begin{tabular}{lllll}\n"); 
    strcat(CodBeamer, "\\cline{1-2}\n"); 
    strcat(CodBeamer, "\\multicolumn{1}{|l|}{\\%\\% \"texto\"} & \\multicolumn{1}{l|}{\\begin{tabular}[c]{@{}l@{}}Har\\'a que se borren todas sus aparciones\\\\ en la entrada.\\end{tabular}}                                    &  &  &  \\\\ \\cline{1-2}\n"); 
    strcat(CodBeamer, "\\multicolumn{1}{|l|}{\\{}           & \\multicolumn{1}{l|}{\\begin{tabular}[c]{@{}l@{}}Tomar\\'a todo eso como parte de la acci\\'on hasta \\\\ que encuentre la llave que lo cierra, \\}\\end{tabular}} &  &  &  \\\\ \\cline{1-2}\n"); 
    strcat(CodBeamer, "\\multicolumn{1}{|l|}{-}            & \\multicolumn{1}{l|}{\\begin{tabular}[c]{@{}l@{}}Hace que la acci\\'on actual aplique tambi\\'en\\\\ para la siguiente.\\end{tabular}}                            &  &  &  \\\\ \\cline{1-2}\n"); 
    strcat(CodBeamer, "&                                                                                                                                                            &  &  & \n"); 
    strcat(CodBeamer, "\\end{tabular}\n"); 
    strcat(CodBeamer, "\\end{table}\n"); 
    strcat(CodBeamer, "\n"); 
    strcat(CodBeamer, "\n"); 

    
    strcat(CodBeamer, ""); 
    strcat(CodBeamer, "\\end{frame}\n"); 

        strcat(CodBeamer,"\\begin{frame}\n\\frametitle{FLEX - continuaci\\'on} \n");
    strcat(CodBeamer, "\\textbf{Acciones} \\newline \n"); 
    strcat(CodBeamer, "El yylex() es una funci\\'on que procesa tokens desde donde lo dejaron la \\'ultima vez. Directivas especiales que se pueden incluir dentro de una acci\\'on \\newline \n"); 
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
    if(strcmp(yytext, "{")==0 || strcmp(yytext, "&")==0 || strcmp(yytext, "}")==0|| strcmp(yytext, "%")==0){
      strcat(CodBeamer,"\\");
      strcat(CodBeamer,yytext);	
}
    else if(strcmp(yytext, "~")==0){
	strcat(CodBeamer,"\\sim");
	}
    else if(strcmp(yytext, "^")==0){
	strcat(CodBeamer,"\\Lambda");
	}
    else if(strcmp(yytext, "^=")==0){
	strcat(CodBeamer,"\\Lambda =");
	}
    else if(strcmp(yytext, "%=")==0){
	strcat(CodBeamer,"\% =");
	}
    else if(strcmp(yytext, "&&")==0){
	strcat(CodBeamer,"\\&\\&");
	}
    else if(strcmp(yytext, "&=")==0){
	strcat(CodBeamer,"\\& =");
	}
  
    else if(strcmp(yytext, "||")==0){
	strcat(CodBeamer,"\\|");
	}
    else if(strcmp(yytext, "|")==0||strcmp(yytext, ">")==0||strcmp(yytext, "<")==0){
	strcat(CodBeamer,"$");
	strcat(CodBeamer,yytext);	
	strcat(CodBeamer,"$");
	}
    else if(strcmp(yytext, "<=")==0){
	strcat(CodBeamer,"$<$=");
	}
    else if(strcmp(yytext, ">=")==0){
	strcat(CodBeamer,"$>$=");
	}
    else if(strcmp(yytext, "|=")==0){
	strcat(CodBeamer,"$|$=");
	}
    else if(strcmp(yytext, "<<=")==0){
	strcat(CodBeamer,"$<<$=");
	}
    else if(strcmp(yytext, ">>=")==0){
	strcat(CodBeamer,"$>>$=");
	}
    else if(strcmp(yytext, "->")==0){
	strcat(CodBeamer,"-$>$");
	}
    else if(strcmp(yytext, ">>")==0){
	strcat(CodBeamer,"$>>$");
	}
    else if(strcmp(yytext, "<<")==0){
	strcat(CodBeamer,"$<<$");
	}
    else if(yytext[0] =='"'){
	analizadorStrings(yytext);
    }
    else if(yytext[0] =='/' && yytext[1]=='*'){
	analizadorStrings(yytext);
    }
    else if(yytext[0] =='/' && yytext[1]=='/'){
	analizadorStrings(yytext);
    }	
    else{
        strcat(CodBeamer,yytext);
     }
    
}
int scanner(void)
{
    int ntoken, vtoken;
    inicializarBeamer();
    ntoken = nextToken();
    
    while(ntoken) {
    	changeline=false;

        numtokens[ntoken]++;
        ntoken = nextToken();
    	strcat(CodBeamer,"\\textcolor{");
    	strcat(CodBeamer,color[ntoken]);
   	    strcat(CodBeamer,"}{");
    	CheckToken(yytext);
	
        strcat(CodBeamer,"} ");
	    if(strcmp(yytext, ";") == 0 || strcmp(yytext, "{") == 0 || strcmp(yytext, "}") == 0 || ntoken==4){
		  strcat(CodBeamer,"\\\\ \n ");
		  linea++;
		  changeline=true;
		}

	    if(linea%10==0 && linea!=1 && changeline==true){
	      strcat(CodBeamer,"\\end{frame}\n");
	      strcat(CodBeamer,"\\begin{frame}\n");
	      strcat(CodBeamer,"\\frametitle{C\\'odigo Analizado}\n");  
	    }
    }
    
    generateHistogram(); 
    generatePieChart(); 
    finalizarBeamer();
    return 0;

}
void analizadorStrings(char* s){
char* val[2];
int len=strlen(s);
for(int i=0;i<len;i++){
	val[0] = s[i];
	val[1] = '\0';
        printf("%c",s[i]);
	if(s[i]=='$'|| s[i]=='#'||s[i]==';' || s[i]=='{' || s[i]=='}'||s[i]=='&' || s[i]== '%'){
	       strcat(CodBeamer, "\\");
	       strcat(CodBeamer, val);     
	       }
        else if(s[i]== '~'){
		strcat(CodBeamer,"\\sim");
	}
        else if(s[i]== '^'){
		strcat(CodBeamer,"\\Lambda");
	}
	else if(s[i]== '|'||s[i]== '>'||s[i]== '<'){
		strcat(CodBeamer,"$");
		strcat(CodBeamer,val);	
		strcat(CodBeamer,"$");
	}
       else if(s[i]== '\\'){
               strcat(CodBeamer,"\\textbackslash ");	
	
}      
       else if(s[i]== '~'&&s[i+1]== 'n'){
               strcat(CodBeamer,"\\~n");}	
       else
	   strcat(CodBeamer, val);
	     


}

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
    strcat(CodBeamer, "\\def\\radius{2.5}\n"); 
    strcat(CodBeamer, "\\def\\cyclelist{{\"magenta\",\"red\",\"green\",\"purple\",\"blue\",\"orange\", \"pink\"}}\n");
    strcat(CodBeamer, "\\newcount\\cyclecount \\cyclecount=1\n");
    strcat(CodBeamer, "\\newcount\\ind \\ind=3\n");
    strcat(CodBeamer, "\\begin{tikzpicture}[nodes = {font=\\sffamily}]\n");
    strcat(CodBeamer, "\\foreach \\percent/\\name in {\n");

    for(int j = 0; j < 8 ; j++){
        percentTokens[j] = (numtokens[j] * 100);
        percentTokens[j]= percentTokens[j] / cantidad; 

    }
    float cantidadPercent = percentTokens[1] + percentTokens[2] + percentTokens[3] + percentTokens[4] + percentTokens[5] + percentTokens[6]+ percentTokens[7];
    
	for(int i = 1; i < 8 ; i++){
	int percentage = (int)percentTokens[i];
	if(percentage != 0){
	char strIPercent[15];
	sprintf(strIPercent, "%.2f", percentTokens[i]);
	strcat(CodBeamer, strIPercent);
	strcat(CodBeamer, "/");
	identifierTokenType(i);
	}
	if (i == 7)
	strcat(CodBeamer, "\n");
	else if (percentage == 0)
	strcat(CodBeamer," ");
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

/*
    Función encargada de quitar los "" al literal del include
*/
char *modificarInclude(char *include){
    
    char *resultado;
    resultado = (char*)malloc(10);
    int n;
    int i;
    n = 0;
    i = 0;

    while(include[n] != '\0'){
        if(include[n] != '"'){

            resultado[i] = include[n];
            i++;
        
        }
        
        n++;
    
    }
    
    return resultado;
}

/*
    Función encargada de evaluar si ya existe un define en la tabla de definiciones
*/

int existeDefine(char *define)
{
    for(int m = 0; m<=numDefines; m++)
    {
  
        /*
            Si encontramos que el valor coincide con la tabla de defines, se retorna verdadero
            Función strcmp: se comparan los dos parámetros que recibe
        */
  
        if(strcmp(defines[m].palabra, define) == 0)
        {

            return m;
        
        }

    }
    
    return -1;

}


/*
    Función encargada de evaluar si ya existe un include en la tabla de inclusiones
*/

bool existeInclude(char *include)
{

    for(int i = 0; i<numIncludes; i++)
    {

      /*Si encontramos que el valor coincide con la tabla de includes, se retorna verdadero*/
      /*función strcmp: se comparan los dos parámetros que recibe*/
      if(strcmp(includes[i], include) == 0)
      {
          return true;
      }

    }
    
    return false;

}

/*
    Función encargada de tomar el valor que tendrá el define, se lee hasta encontrar un salto de línea
*/
char* tomarValorDefine(){
    
    char* valorDefine;
    int ntoken;
    valorDefine = (char*)malloc(10);

    ntoken = nextToken();
    
    /*
        Se lee hasta el salto de línea
    */
    while(strcmp(yytext, "\n") != 0){
        
        strcat(valorDefine, yytext); //Se van concatenando los valores que se van encontrando
        
        ntoken = nextToken();   

    }

    return valorDefine;

}

/*
    Función encargada de recibir un valor de un define y luego descomponer este valor según estén en la tabla de defines
*/
char *descomponerHileraDefine(char *valorDefine){
    
    int i = 0; //Contador para el valorDefine
    int a = 0; //Contador para el temporal
    char temporal[100000] = ""; //El temporal va tomando los valores por espacios
    char *resultado; //El valor que se retornará
    char *n; //El valor que se obtendrá de llamar recursivamente a la función
    int existe; //El índice que indica en cuál posición del array de defines está el elemento buscado
 
    

    resultado  = (char*)malloc(10);
    
    while(valorDefine[i] != '\0'){

        /*
            Se lee hasta que se encuentre un espacio
        */
        if(!isspace(valorDefine[i])){

            temporal[a] = valorDefine[i];
            a++;

        }
        

        /*
            Cuando se encuentra el espacio
        */
        else{
        
            existe = existeDefine(temporal); //Se busca en cuál índice se encuentra el temporal

            /*
                Si no existe, solamente se concatena
            */
            if (existe == -1){
                
                strcat(resultado, temporal);

            }

            /*
                En caso contrario, busco el valor en la tabla, llamando a la función recursivamente
            */
            else{
                
                char *n;
                n = descomponerHileraDefine(defines[existe].vDefine);
                strcat(resultado, n);

            }

            /*
                Se reinicia el temporal
            */
            a = 0;
            memset(&temporal[0], 0, sizeof(temporal));
        


        }

        i++;


    }

    /*
        Después del EOF, aún se tendrá un elemento en el temporal
    */
    existe = existeDefine(temporal);

    if (existe == -1){

        strcat(resultado, temporal);

    }

    /*En caso contrario, lo concateno con el valor en la tabla*/
    else{

        char *n;
        n = descomponerHileraDefine(defines[existe].vDefine);
        strcat(resultado, n);
    
    }

    return resultado;

    
}

/*
    Función que se encarga de realizar las funcionalidades del preprocesador
*/
void preprocesador(char *archivo, FILE* archivoTemporal){

    int ntoken;         //El token actual
    char *valorDefine;  //El valor que tomará un define
    char *concatenar;   //Es el valor de un elemento en la tabla de defines, se obtendrá de manera descompuesta
    int existe;         //El índice que indica en cuál posición del array de defines está el elemento buscado
    char *includeArreglado; //El valor del include sin los ""

    ntoken = nextToken();
    valorDefine = (char*)malloc(10);
    
    while(ntoken) {
        
        /*
            El preprocesador encuentra un include
        */
        
        if(ntoken == INCLUDE){
            
            

            ntoken = nextToken(); //Se obtiene el siguiente token para evaluar 

            /*
                Se leen tokens hasta que no hayan espacios
            */

            while(ntoken == SPACE){
                
                ntoken = nextToken();

            }
            
            /*
                Debido a que los define son literales
            */  

            if(ntoken == LITERAL){
                
                numIncludes++;

                FILE* siguienteArchivo; //Se creará un nuevo archivo

                includeArreglado = modificarInclude(yytext); //Se obtiene el include sin ""
                


                /*
                    Si el include es diferente al archivo que lo invocó
                */

                if(existeInclude(includeArreglado) == false){
                    
                    includes[numIncludes] = includeArreglado; //Se agrega a la tabla

                    
                    
                    siguienteArchivo = fopen(includeArreglado, "r"); //Se pone en modo lectura, FALTA: función que quite los "" de un literal
                    
                    

                    /*
                        Se le indica a flex cuál es el archivo actual que se está leyendo
                    */

                    yyin = siguienteArchivo; 
                    yy_switch_to_buffer(yy_create_buffer( yyin, 50));
                    preprocesador(yytext, siguienteArchivo); //Se llama de nuevo a la función, pero esta vez con el siguiente archivo incluído
                    
                    /*
                        Después de la llamada recursiva, se borra la inclusión
                    */
                    
                    includes[numIncludes] = ""; 
                    numIncludes--;

                    yyin = archivoTemporal; //Se le dice a flex cuál archivo se estará leyendo
                    yy_switch_to_buffer(yy_create_buffer( yyin, 50));
                }

                /*
                    Si el include es igual al archivo que lo invocó
                */

                else{

                    printf("Inclusión duplicada de %s", includeArreglado); //Se notifica el error, revisar esta validación
                }
                    
                
            }

        }

        

        /*
            El preprocesador encuentra un define
        */
        else if(ntoken == DEFINE){


            ntoken = nextToken(); //Se obtiene el siguiente token para evaluar


            /*
                Se leen tokens hasta que no hayan espacios
            */
            
            while(ntoken == SPACE){
                
                ntoken = nextToken();
            
            }


            existe = existeDefine(yytext); //Se evalúa si existe el token
            numDefines++; //Se suma un nuevo define al contador

            /*
                Se inicializan los valores del array de defines, debido a que los elementos son de tipo char *
            */
            defines[numDefines].palabra = (char*)malloc(10);
            defines[numDefines].vDefine = (char*)malloc(10);
                

            /*
                Si no existe, solo se agrega un nuevo elemento a la lista de defines
            */
            
            if(existe == -1){ 
                
                strcpy(defines[numDefines].palabra, yytext);
                ntoken = nextToken(); //Para no tomar en cuenta el espacio
                valorDefine = tomarValorDefine(); //Se llama a la función que toma el valor que tendrá el define
                strcpy(defines[numDefines].vDefine, valorDefine); //Se copia el valor obtenido al valor que tendrá el define
            
            }

            /*
                Si existe, se cambia el valorDefine en la posición "existe" del array de defines    
            */

            else{

                ntoken = nextToken();
                valorDefine = tomarValorDefine(); //Se llama a la función que toma el valor que tendrá el define
                strcpy(defines[existe].vDefine, valorDefine);
                numDefines--;  //Debido a que se repite un define, el número total se debe restar en uno, para nivelar el array
                

            }

        }

        /*
            El preprocesador encuentra un identificador, por lo que se dispondrá a reemplazar la hilera por una existente
        */

        else if(ntoken == IDENTIFIER){

            existe = existeDefine(yytext);

            /*
                Si no existe el identificador en la tabla de defines
            */

            if(existe == -1){

                fputs(yytext, tmpFile); //Se imprime el valor actual
            
            }

            /*
                Si existe el identificador en la tabla de defines
            */

            else{
                
                concatenar = descomponerHileraDefine(yytext);
                fputs(concatenar, tmpFile);
                //fputs(defines[existe].vDefine, tmpFile); //Se obtiene la posición de la tabla en donde está y se imprime su valor correspondiente

            }

        }

        /*
            Si no es ninguno de los tres anteriores, solo se imprimirá el valor actual, no se toma en cuenta a los comentarios
        */

        else if (ntoken != COMMENT){

            fputs(yytext, tmpFile);

        }

        printf("%s\n", yytext);
        ntoken = nextToken();
        
    }

}

void yyerror(char *texto,char *simbolo, int linea){
     
     /*
        Cuando aún se encuentra en el preprocesamiento, se escribe en el archivo
    */
    if(preproceso == false){
        printf("%s\n", yytext);
        fputs(yytext, tmpFile);
    
    }

    /*
        Cuando esté en el scanner, deberá imprimir el error correspondiente
    */

    else{
        
        printf(texto,simbolo,linea);
        strcat(CodBeamer,"\\colorbox{red}{");
        if(strcmp(yytext, "$")==0 || strcmp(yytext,"#")==0){
            strcat(CodBeamer, "\\");
        }
        strcat(CodBeamer, simbolo);
        strcat(CodBeamer,"}");
    
    }

};

void imprimirArchivoEntrada(FILE *temporal){
    int in_char;
    while ((in_char = getc(temporal)) != EOF){
        putchar(in_char);
    } 
    putchar('\n');
}
void openfilepreprocess(FILE *f, char *nombreArchivo){
    if(seLeyoArchivo(f))
    {
        printf("Se pudo leer el archivo correctamente\n");
        tmpFile = fopen("config.c", "wt");
        preprocesador(nombreArchivo, f);
        preproceso = true;
        fclose(tmpFile);
	//error=false;


    }
    else
    {
        printf("No se pudo leer el archivo correctamente");
    } 
    

}
void limpiarDocumento(char *f){
	fclose(fopen(f, "w"));
}



int main(int argc, char *argv[])
{
    

    /*
        Se valida que se hayan digitado los archivos de entrada en la terminal
    */

    if(argv[1] == NULL){

        printf("No se ingresó ningún archivo de entrada");
     
    }

    /*
        En este caso, se llama a las funcionalidades del preprocesador
    */
    else{
        printf("HOLA");
        FILE *archivoParaPreprocesar;
        tmpFile = fopen("config.c", "wt");
        archivoParaPreprocesar  = fopen(argv[1], "r");
        

        /*
            Se le indica a flex cuál es el archivo actual que se está leyendo
        */
        yyin = archivoParaPreprocesar;  
        yy_switch_to_buffer(yy_create_buffer( yyin, 50));     
        
        preprocesador(argv[1], archivoParaPreprocesar); //Se llama a la función del preprocesador con el archivo de entrada
        printf("Termino");
        
        fclose(archivoParaPreprocesar);
        fclose(tmpFile);
        
     }


     /*
    FILE *f = leerArchivo(argv[1]);
    openfilepreprocess(f, argv[1]);
    if (error == false){

        FILE *temporal = fopen("config.c", "r");
        imprimirArchivoEntrada(temporal);
        //fclose(temporal);
        //scanner();
        //system("pdflatex main.tex");
        //system("evince --presentation main.pdf");
    }



    limpiarDocumento("config.c");*/


    return 0; 
}


