#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int tareaId;//numerado en ciclo iterativo
    char *descripcion;
    int duracion; //10-100
};
typedef struct Tarea tarea;
struct Nodo{
    tarea T;
    struct Nodo *next;
};
typedef struct Nodo ntarea;

//          Funciones
ntarea * cargarNodo(int id);
void crearNodo(ntarea ** start, int id);
void mostrarTareas(ntarea * start);
void liberar(ntarea ** start);
//          Main
int main(){
    srand(time(NULL));
    ntarea * tareaP=NULL;
    printf("Ingrese la cantidad de tareas: ");
    int cantTareas;
    scanf("%d",&cantTareas);
    getchar();
    fflush(stdin);
    for(int i=0;i<cantTareas;i++){
        crearNodo(&tareaP,i);
    }
    mostrarTareas(tareaP);
    liberar(&tareaP);
    return 0;
}

//          Funciones
ntarea * cargarNodo(int id)
{
    ntarea * nodoAux=(ntarea*)malloc(sizeof(ntarea));
    nodoAux->T.tareaId=id+1;
    fflush(stdin);
    printf("Ingrese una descripción: ");
    char * buffer=(char*)malloc(sizeof(char)*200);
    fgets(buffer,200,stdin);
    /* getchar(); */
    fflush(stdin);
    nodoAux->T.descripcion=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(nodoAux->T.descripcion,buffer);
    free(buffer);
    nodoAux->T.duracion=rand()%(100-10+1)+10;
    nodoAux->next=NULL;
    return nodoAux;
}

void crearNodo(ntarea ** start, int id)
{
    ntarea * nNodo;
    nNodo=cargarNodo(id);
    if(*start == NULL)
    {
        *start = nNodo;
    }
    else
    {
        nNodo->next=*start;
        *start=nNodo;
    }
}

void liberar(ntarea ** start)
{
    ntarea * recorrer = *start;
    ntarea * bor;
    while (recorrer != NULL)
    {
        bor = recorrer;
        recorrer = recorrer->next;
        free(bor->T.descripcion);
        free(bor);
    }
    
}

void mostrarTareas(ntarea * start)
{
    ntarea * nAux;
    nAux=start;
    while (nAux != NULL)
    {
        printf("ID %d\n",nAux->T.tareaId);
        //printf("Descripción: %s\n",nAux->T.descripcion);
        puts(nAux->T.descripcion);
        printf("Duracioń: %d\n",nAux->T.duracion);
        nAux = nAux->next;
    }
    
}