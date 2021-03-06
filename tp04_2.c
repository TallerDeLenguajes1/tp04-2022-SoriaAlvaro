#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Tareas {
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //entre 10-100
};
typedef struct Tareas tarea;


tarea * cargarTareas(int iD);
bool confirmarTarea();
void mostrarTarea(tarea * tareas);
void mostrarTareas(tarea ** tareas, int cantTareas);
void controlTareas(tarea **tareasR,tarea **tareasP, int cantTareas);
void liberarTarea(tarea **tareasP,tarea **tareasR,int cantTareas);
void buscarTarea(tarea **tareasP,tarea **tareasR, int cantTareas);

int main(){
    srand(time(NULL));

    printf("\t\tIngrese la cantidad de tareas: ");
    int cantTareas;
    scanf("%d",&cantTareas);
    getchar();
    fflush(stdin);
    
    tarea **tareasPendientes,**tareasRealizadas;
    tareasPendientes=(tarea**)malloc(sizeof(tarea*)*cantTareas);
    tareasRealizadas=(tarea**)malloc(sizeof(tarea*)*cantTareas);

    for(int i=0; i < cantTareas; i++){
        tareasPendientes[i]=cargarTareas((i+1));
    }
    printf("\t\tTAREAS PENDIENTES\n\n");
    mostrarTareas(tareasPendientes,cantTareas);
    controlTareas(tareasRealizadas,tareasPendientes,cantTareas);
    printf("\t\tTAREAS REALIZADAS\n\n");
    mostrarTareas(tareasRealizadas,cantTareas);
    printf("\t\tTAREAS PENDIENTES\n\n");
    mostrarTareas(tareasPendientes,cantTareas);
    buscarTarea(tareasPendientes,tareasRealizadas,cantTareas);
    getchar();
    liberarTarea(tareasPendientes,tareasRealizadas,cantTareas);
    free(tareasPendientes);
    free(tareasRealizadas);

    return 0;
}

tarea * cargarTareas(int iD){
    tarea * nTarea=(tarea*)malloc(sizeof(tarea));
    
    nTarea->tareaID=iD;

    printf("\t\tIngrese la descripción de la tarea: %d\n",nTarea->tareaID);
    char *buffer=(char*)malloc(sizeof(char)*200);
    fgets(buffer,200,stdin);
    fflush(stdin);

    nTarea->descripcion=(char*)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(nTarea->descripcion,buffer);
    free(buffer);
    nTarea->duracion=rand()%(100-10+1)+10;

    return nTarea;
}

bool confirmarTarea(){
    printf("\t\tRealizó la tarea?\n\t\tY para confirmar.\n\t\tCualquier letra para denegar.\n");
    char letra;
    scanf("%c",&letra);
    fflush(stdin);
    getchar();
    
    if(letra == 'y' || letra == 'Y'){
        return true;
    }else{
        return false;
    }
}

void mostrarTarea(tarea * tareas){
    printf("\t\tID tarea %d\n", tareas->tareaID);
    printf("\t\t%s",tareas->descripcion);
    /* puts(tareas->descripcion); */
    printf("\t\tDuración %d",tareas->duracion);
    printf("\n=\t*\t=\t*\t=\t*\t=\t*\t=\t*\t=\n");
}

void mostrarTareas(tarea ** tareas, int cantTareas){
    for(int i=0;i<cantTareas;i++){
        if(tareas[i] != NULL){
            mostrarTarea(tareas[i]);
        }else{
            continue;
        }
    }
}

void controlTareas(tarea **tareasR,tarea **tareasP, int cantTareas){
    for(int i=0;i<cantTareas;i++){
       printf("\t\tTarea %d\n", i+1);
       
       if(confirmarTarea()){
           tareasR[i]=(tarea*)malloc(sizeof(tarea));
           tareasR[i]=tareasP[i];
           tareasP[i]=NULL;
       }else{
           tareasR[i]=NULL;
       }
    }
}

void liberarTarea(tarea **tareasP,tarea **tareasR,int cantTareas){
    for(int i=0;i<cantTareas;i++){
        if(tareasP[i]!=NULL){
          free(tareasP[i]->descripcion);
          free(tareasP[i]);
        }
        if(tareasR[i]!=NULL){
          free(tareasR[i]->descripcion);
          free(tareasR[i]);
        }
    }
}
void buscarTarea(tarea **tareasP,tarea **tareasR, int cantTareas){

    printf("\t\t\tDonde desea buscar?\n\t\t1)En Tareas Pendientes\n\t\t2)En Tareas Realizadas\n");
    int op;
    scanf("%d",&op);
    fflush(stdin);
    getchar();
    switch (op){
        case 1:
            printf("\n\t\t\tIngrese la palabra clave \n\t\tde la tarea que desea buscar: ");
            char *aux=(char*)malloc(sizeof(char)*100);
            fgets(aux,100,stdin);
            for(int i=0;i<cantTareas;i++){
               if(tareasP!=NULL){
                    int tam1= strlen(tareasP[i]->descripcion),
                    tam2=strlen(aux), j=0;
                    char c;
                    if(tam2 > tam1){
                        printf("\t\tLa palabra buscada\n\t\tes mas grande\n");
                        return NULL;
                    }else{
                        c=aux[0];
                        while (j < tam1)
                        {
                            if(tareasP[i]->descripcion[j]== c){
                                if(strncmp(&tareasP[i]->descripcion[j],aux,tam2)==0){
                                    mostrarTarea(tareasP[i]);
                                }
                            }
                            j++;
                        }
                    }
               }else{
                   continue;
               }
            }
            break;
        case 2:
            printf("\n\t\t\tIngrese el ID \n\t\tde la tarea que desea buscar: ");           int id;
            scanf("%d",&id);
            fflush(stdin);
            for(int i=0;i<cantTareas;i++){
                if((i+1)==id && tareasR[i]!=NULL){
                    mostrarTarea(tareasR[i]);
                }else if(tareasR[i]==NULL && (i+1)==id){
                        printf("\t\tNo se encontró la tarea\n");
                }
                if(id>cantTareas || cantTareas < 0){
                    printf("\t\tNo se encontró la tarea\n");
                }
                if(tareasR[i]==NULL){
                    continue;
                }
            }
            break;
    }
}
