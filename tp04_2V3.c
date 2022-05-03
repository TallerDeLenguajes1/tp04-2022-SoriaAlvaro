#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
struct Tarea
{
    int tareaId; // numerado en ciclo iterativo
    char *descripcion;
    int duracion; // 10-100
};
typedef struct Tarea tarea;
struct Nodo
{
    tarea T;
    struct Nodo *next;
};
typedef struct Nodo nTar;

//      funciones
nTar *cargarNodo(int id);
void insertarNodo(nTar **nodo, int cantTareas);
void mostrarNodo(nTar *nodo);
void mostrarNodos(nTar *nodo);
bool confirmarTarea(nTar * nodo);
void moverTareas(nTar ** nodoP, nTar ** nodoR);
void insertarAlFinal(nTar ** nodo,int i);
nTar * buscarNodo(nTar * nodo, int idBusc);
void buscarPorID(nTar * nodo);
//      Main
int main()
{   
    srand(time(NULL));
    printf("\n--\t--\t--\t-- Tareas --\t--\t--\t--\n");
    printf("Ingrese la cantidad de tareas: ");
    int cantTareas;
    scanf("%d",&cantTareas);
    getchar();
    fflush(stdin);
    nTar * pendientes, * realizadas;
    pendientes=NULL;
    realizadas=NULL;
    insertarNodo(&pendientes,cantTareas);
    printf("\n--\t--\t--\t-- Tareas Pendientes --\t--\t--\t--\n");
    mostrarNodos(pendientes);
    moverTareas(&pendientes,&realizadas);
    printf("\n--\t--\t--\t-- Tareas Realizadas --\t--\t--\t--\n");
    mostrarNodos(realizadas);
    printf("\n--\t--\t--\t-- Tareas Pendientes --\t--\t--\t--\n");
    mostrarNodos(pendientes);
    printf("\n--\t--\t--\t-- Tareas 2 --\t--\t--\t--\n");
    insertarAlFinal(&pendientes,3);
    insertarAlFinal(&pendientes,4);
    insertarAlFinal(&pendientes,5);
    printf("\n--\t--\t--\t-- Tareas Pendientes 2 --\t--\t--\t--\n");
    mostrarNodos(pendientes);
    buscarPorID(pendientes);
    return 0;
}
//      funciones
nTar *cargarNodo(int id){
    nTar *nuevaTarea = (nTar *)malloc(sizeof(nTar));
    nuevaTarea->T.tareaId = id + 1;
    fflush(stdin);
    printf("\tIngrese una descripción\n\tde la tarea:");
    char *buffer = (char *)malloc(sizeof(char) * 200);
    fgets(buffer, 200, stdin);
/*     getchar(); */
    fflush(stdin);
    nuevaTarea->T.descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(nuevaTarea->T.descripcion, buffer);
    nuevaTarea->T.duracion = rand() % (100 - 10 + 1) + 10;
    nuevaTarea->next = NULL;
    return nuevaTarea;
}
void insertarNodo(nTar **nodo, int cantTareas){
    nTar *nuevoNodo;
    for (int i = 0; i < cantTareas; i++)
    {
        nuevoNodo = cargarNodo(i);
        if (*nodo == NULL)
        {
            *nodo = nuevoNodo;
        }
        else
        {
            nuevoNodo->next = *nodo;
            *nodo=nuevoNodo;
        }
    }
}
void insertarAlFinal(nTar ** nodo,int i){
    nTar * nuevoNodo=cargarNodo(i);
    nTar * aux=*nodo;
    if(aux == NULL){

        aux=nuevoNodo;
        *nodo=aux;
    }else{
        while(aux->next !=NULL){
            aux=aux->next;
        }
        aux->next=nuevoNodo;
    }
}
void mostrarNodo(nTar *nodo){
    nTar *auxNodo = nodo;
    printf("Tarea %d\nDescripción: %sDuración: %d", auxNodo->T.tareaId, auxNodo->T.descripcion, auxNodo->T.duracion);
    printf("\n--\t--\t--\t--\t--\t--\t--\t--\t--\t--\n");
}
void mostrarNodos(nTar *nodo){
    nTar *auxNodo = nodo;
    while (auxNodo != NULL)
    {
        if(auxNodo!=NULL)
        {
            mostrarNodo(auxNodo);
            auxNodo = auxNodo->next;
        }
        else{auxNodo=auxNodo->next;}
    }
}
bool confirmarTarea(nTar * nodo){
    printf("\n--\t--\t--\t--\t--\t--\t--\t--\t--\t--\n");
    printf("\t\t\tTerminó la tarea %d?\n\t\tY para confirmar\t\tN para denegar.\n",nodo->T.tareaId);
    char letra;
    do
    {
        fflush(stdin);
        scanf("%c",&letra);
        getchar();

        if(letra != 'y' && letra != 'Y' && letra != 'n' && letra != 'N')
        {
            printf("ELIJA UNA OPCIÓN CORRECTA");
        }
        if(letra == 'y' || letra == 'Y'){
            return true;
        }
        if(letra == 'n' || letra == 'N'){
            return false;
        }
    }while(letra != 'y' && letra != 'Y' && letra != 'n' && letra != 'N');
}
void moverTareas(nTar ** nodoP, nTar ** nodoR){
    nTar * aux=*nodoP;
    nTar * anterior=NULL;
    while(aux != NULL){
        if(*nodoP != anterior){
            if(confirmarTarea(*nodoP)){
                *nodoP=(*nodoP)->next;
                aux->next=*nodoR;
                *nodoR=aux;
                aux=*nodoP;
            }else{
                anterior=*nodoP;
            }
        }else{
            anterior=aux;
            aux=aux->next;
            if(aux != NULL){
                if(confirmarTarea(*nodoP)){
                    anterior->next=aux->next;
                    aux->next=*nodoR;
                    *nodoR=aux;
                    aux=anterior;
                }
            }
        }
    }
}

nTar * buscarNodo(nTar * nodo, int idBusc){
    nTar * aux= nodo;
    while(aux && aux->T.tareaId != idBusc){
        aux=aux->next;
    }
    return aux;
}

void buscarPorID(nTar * nodo){
    printf("\n--\t--\t--\t-- Buscar por id --\t--\t--\t--\n");
    printf("Ingrese el id buscado: ");
    int id;
    scanf("%d",&id);
    fflush(stdin);
    nTar * nodoAux = buscarNodo(nodo,id);
    mostrarNodo(nodoAux);
}