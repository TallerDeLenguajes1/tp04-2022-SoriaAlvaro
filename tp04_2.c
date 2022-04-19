#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Tarea {
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //entre 10-100
};


int main (){
    srand(time(NULL));
    int cantTareas;
    printf("Ingrese la cantidad de tareas que quieres cargar: ");
    scanf("%d", &cantTareas);
    getchar();
    struct Tarea **tareasPendientes, **tareasRealizadas;
    tareasPendientes=(struct Tarea**)malloc(sizeof(struct Tarea)*cantTareas);
    /* tareasRealizadas=(struct Tarea**)malloc(sizeof(struct Tarea)*cantTareas); */


    char *buffer;
    buffer=(char*)malloc(sizeof(char)*200);
    for(unsigned i=0; i<cantTareas; i++){
        tareasPendientes[i]->tareaID=i+1;
        printf("Ingrese la descripcion: %d\n",i+1);
        gets(buffer);
        fflush(stdin);
        tareasPendientes[i]->descripcion=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(tareasPendientes[i]->descripcion,buffer);
        tareasPendientes[i]->duracion=rand()%(100-10+1)+10;
    }

    free(buffer);

    printf("TAREAS PENDIENTES: \n");
    for(unsigned i=0;i<cantTareas;i++){
        printf("ID %d", tareasPendientes[i]->tareaID);
        printf("\n");
        puts(tareasPendientes[i]->descripcion);
        printf("\n");
        printf("duración: %d", tareasPendientes[i]->duracion);
    }

    for(unsigned i=0;i<cantTareas;i++){
        free(tareasPendientes[i]);

    }

    free(tareasPendientes);

    return 0;
}