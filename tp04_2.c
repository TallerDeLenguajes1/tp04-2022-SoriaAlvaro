#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int tareaID;
    char *descripcion;
    int duracion; //10 - 100
};

typedef struct Tarea tar;

struct Nodo
{
    tar t;
    struct Nodo *siguiente;
};

typedef struct Nodo nod;


int main(){

    nod * start;
    return 0;
}


nod * crearListaVacia(){return NULL;}
nod * cargaNodo(int iD){
    nod * nuevoNodo;
    nuevoNodo=(nod*)malloc(sizeof(nod));
    nuevoNodo->t.tareaID= iD;
    nuevoNodo->t.duracion= rand()%(100-10+1)+10;
    printf("\n\t=\t=\t=\t=\t=\t=\t=\t=\t=\t=\t=\t=\t=\n");
    printf("\t\t\tINGRESE UNA DESCRIPCIÓN: ");
    char *buffer;
    buffer=(char*)malloc(sizeof(char)*200);
    fgets(buffer,200,stdin);
    nuevoNodo->t.descripcion=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(nuevoNodo->t.descripcion,buffer);
    free(buffer);
    nuevoNodo->siguiente=crearListaVacia();
    return nuevoNodo;
}

void insertarNodo(nod ** start, int cantTareas){
    nod * nuevoNodo;
    
}