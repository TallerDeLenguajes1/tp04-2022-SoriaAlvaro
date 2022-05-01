#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
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
void crearNodo2(ntarea ** start, int cantT);
void mostrarTareas(ntarea * start);
void liberar(ntarea ** start);
bool confirmarTarea(ntarea * tpend);
void moverTareas(ntarea * tPendiente, ntarea ** tRealizadas);
void mostrarNumTarea(ntarea * tarea);
void buscarTareasID(ntarea * tarea, int cantTareas);
//          Main
int main(){
    printf("\n--\t--\t--\t-- Tareas --\t--\t--\t--\n");
    srand(time(NULL));
    ntarea * tareaP=NULL;
    ntarea * tareaR=NULL;
    printf("\t\t\tIngrese la cantidad de tareas: ");
    int cantTareas;
    scanf("%d",&cantTareas);
    getchar();
    fflush(stdin);
    crearNodo2(&tareaP,cantTareas);
    printf("\n--\t--\t--\t-- Tareas Pendientes \t--\t--\t--\t--\n");
    mostrarTareas(tareaP);
    buscarTareasID(tareaP,cantTareas);
    moverTareas(tareaP,&tareaR);
    printf("\n--\t--\t--\t-- Tareas Realizadas \t--\t--\t--\t--\n");
    mostrarTareas(tareaR);
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
void crearNodo2(ntarea ** start, int cantT)
{
        ntarea * nNodo;
    for(int i=0;i<cantT;i++)
    {
        nNodo=cargarNodo(i);
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
        printf("\n--\t--\t--\t--\t--\t--\t--\t--\t--\t--\n");
        printf("\n\t\t\tTarea %d\n\t\t\tDescripción: %s\t\t\tDuración: %d\n",nAux->T.tareaId,nAux->T.descripcion,nAux->T.duracion);
        nAux = nAux->next;
    }
    
}

bool confirmarTarea(ntarea * tpend)
{
    printf("\n--\t--\t--\t--\t--\t--\t--\t--\t--\t--\n");
    printf("\t\t\tTerminó la tarea %d?\n\t\tY para confirmar\t\tN para denegar.\n",tpend->T.tareaId);
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

void moverTareas(ntarea * tPendiente, ntarea ** tRealizadas)
{
    ntarea * tAux= tPendiente;
    while (tAux != NULL)
    {
        if(confirmarTarea(tAux))
        {
            ntarea *nuevoNodo = tAux;
            tAux = tAux->next;
            nuevoNodo->next = *tRealizadas;
            *tRealizadas = nuevoNodo;
        }
        else
        {
            tAux = tAux->next;
        }
    }
    
}

void mostrarNumTarea(ntarea * tarea)
{
    while(tarea != NULL)
    {   printf("Tarea %d \t",tarea->T.tareaId);
        tarea=tarea->next;
    }
}
void buscarTareasID(ntarea * tarea, int cantTareas)
{
    printf("\n--\t--\t-- Buscar Tareas Pendientes --\t--\t--\n");
/*     mostrarNumTarea(tarea); */
    ntarea * aux=tarea;
    while(aux != NULL)
    {
        printf("Tarea %d \t",aux->T.tareaId);
        aux=aux->next;
    }
    printf("\n\t\t\tIngrese el id que quiere buscar: ");
    int id;
    do
    {
        fflush(stdin);
        scanf("%d",&id);
        getchar();
        if(!(id > 0 && id<=cantTareas))
        {
            printf("ELIJA UNA OPCIÓN CORRECTA: ");
        }
        else{
            while(tarea != NULL)
            {
                if(tarea != NULL)
                {
                    if(tarea->T.tareaId==id)
                    {
                        printf("\n\t\t\tTarea %d\n\t\t\tDescripción: %s\t\t\tDuración: %d\n",tarea->T.tareaId,tarea->T.descripcion,tarea->T.duracion);
                    }
                }
                tarea= tarea->next;
            }
        }
    }while(!(id > 0 && id<=cantTareas));
}

