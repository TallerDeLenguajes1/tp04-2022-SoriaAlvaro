#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Tarea {
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //entre 10-100
};


bool confirmarTarea();

int main (){
    int cantTareas;
    printf("Ingrese la cantidad de tareas que quieres cargar: ");
    scanf("%d", &cantTareas);
    getchar();

    //Asignando memoria dinamica a puntero de estructuras
    struct Tarea **tareasPendientes, **tareasRealizadas;
    tareasPendientes=(struct Tarea**)malloc(sizeof(struct Tarea*)*cantTareas);
    tareasRealizadas=(struct Tarea**)malloc(sizeof(struct Tarea*)*cantTareas);


    srand(time(NULL));

    //Asignando memoria dinamica a buffer de 200 caracteres
    char *buffer;
    buffer=(char*)malloc(sizeof(char)*200);

    for(int i=0; i<cantTareas; i++){
        //Asignando memoria dinamica para estructuras
        tareasPendientes[i]=(struct Tarea*) malloc(sizeof(struct Tarea));
        tareasPendientes[i]->tareaID=i+1;
        printf("\nIngrese la descripcion: %d\n",i+1);
        fgets(buffer,200,stdin);
        fflush(stdin);
        //Asignando memoria dinamica para caracteres
        tareasPendientes[i]->descripcion=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(tareasPendientes[i]->descripcion,buffer);
        tareasPendientes[i]->duracion=rand()%(100-10+1)+10;
        printf("\n===================================================\n\n");
    }

    free(buffer);

    printf("\n\tTAREAS PENDIENTES: \n\n===================================================\n");
    for(int i=0;i<cantTareas;i++){
        printf("ID %d\n\n", tareasPendientes[i]->tareaID);
/*         printf("\n"); */
        puts(tareasPendientes[i]->descripcion);
/*         printf("\n"); */
        printf("duración: %d\n", tareasPendientes[i]->duracion);
        printf("===================================================\n");
    }

    for(int i=0;i<cantTareas;i++){
        if(confirmarTarea()){
            //Asignando memoria dinamica para estructuras cuando el valor sea true
            tareasRealizadas[i]=(struct Tarea*) malloc(sizeof(struct Tarea));
            //pasando las tareas relaizadas a la otra estructura
            tareasRealizadas[i]=tareasPendientes[i];
        }
    }

    printf("\n\tTAREAS REALIZADAS: \n\n===================================================\n");
    for(int i=0;i<cantTareas;i++){
        printf("ID %d\n\n", tareasRealizadas[i]->tareaID);
/*         printf("\n"); */
        puts(tareasRealizadas[i]->descripcion);
/*         printf("\n"); */
        printf("duración: %d\n", tareasRealizadas[i]->duracion);
        printf("===================================================\n");
    }

    for(int i=0;i<cantTareas;i++){
        free(tareasPendientes[i]);
        free(tareasRealizadas[i]);
    }

    free(tareasPendientes);
    free(tareasRealizadas);

    return 0;
}

bool confirmarTarea(){
    printf("\tTerminó la tarea?.\n\tEscriba 'y' para confirmar.\n\tCualquier otra letra para denegar.\n\n");
    char letra;
    scanf("%c",&letra);
    getchar();
    fflush(stdin);
    if(letra == 'y' || letra=='Y'){
        return true;
    }else{
        return false;
    }
}