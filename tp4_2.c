#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
    int tareaID;
    char *descripcion;
    int duracion;
}tarea;

int main(){
    srand(time(NULL)); //Instrucción que inicializa el generador de números aleatorios

    //Pedimos la cantidad de tareas
    int cantTareas;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);

    //creamos los punteros dobles y reservamos memoria
    tarea **tareasPendientes;
    tareasPendientes = (tarea **) malloc(sizeof(tarea *) * cantTareas);
    
    tarea **tareasRealizadas;
    tareasRealizadas = (tarea **) malloc(sizeof(tarea *) * cantTareas);

    //Puntero auxiliar
    char *buff;
    buff = (char *) malloc(sizeof(char) * 100);

    //Cargo las tareas pendientes
    for(int i=0; i<cantTareas; i++){
        printf("Ingrese una descripcion de la tarea %d: ", i+1);
        fflush(stdin);
        gets(buff);
        fflush(stdin);
        tareasPendientes[i] = (tarea *) malloc(sizeof(tarea)); //reservo memoria para cargar la tarea
        tareasPendientes[i]->tareaID = i+1;
        tareasPendientes[i]->descripcion = (char *) malloc(sizeof(char) * (strlen(buff)+1)); //reservo memoria para cargar la descripcion
        strcpy(tareasPendientes[i]->descripcion, buff); //paso del auxiliar a la descr. de la tarea
        tareasPendientes[i]->duracion = (rand()%90)+10;   
    }

    //Listamos tareas realizadas
    for(int i=0; i<cantTareas; i++){
        printf("\nTarea %d -----------------------------------------------\n", tareasPendientes[i]->tareaID);
        printf("%d\n", tareasPendientes[i]->tareaID);
        puts(tareasPendientes[i]->descripcion);
        printf("%d\n", tareasPendientes[i]->duracion);
    }
    free(buff);

    //Cargamos las tareas realizadas
    char respuesta;
    for(int i=0; i<cantTareas; i++){
        printf("\n- Realizo la tarea %d?", i+1);
        fflush(stdin);
        printf("\nDescripcion: %s\n", tareasPendientes[i]->descripcion);
        scanf("%c",&respuesta);
        tareasRealizadas[i] = (tarea *) malloc(sizeof(tareasPendientes[i]));
        if(respuesta == 's' || respuesta == 'S'){
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }else{
            tareasRealizadas[i] = NULL;
        }
    }

    //Mostrar tareas pendientes y realizadas
    printf("\n ----- Tareas realizadas -----\n");
    for(int i=0; i<cantTareas; i++){
        if(tareasRealizadas[i] != NULL){
            printf("\n- tarea %d\n", tareasRealizadas[i]->tareaID);
            printf("%d\n", tareasRealizadas[i]->tareaID);
            puts(tareasRealizadas[i]->descripcion);
            printf("%d\n", tareasRealizadas[i]->duracion);
        }
    }

    printf("\n ----- Tareas pendientes -----\n");
    for(int i=0; i<cantTareas; i++){
        if(tareasPendientes[i] != NULL){
            printf("\n- tarea %d\n", tareasPendientes[i]->tareaID);
            printf("%d\n", tareasPendientes[i]->tareaID);
            puts(tareasPendientes[i]->descripcion);
            printf("%d\n", tareasPendientes[i]->duracion);
       }
    }

    //Liberamos memoria
    for(int i=0; i<cantTareas; i++){
        if(tareasPendientes[i] != NULL){
            free(tareasPendientes[i]->descripcion);
        }else{
            free(tareasRealizadas[i]->descripcion);
        }
    }
    free(tareasPendientes);
    free(tareasRealizadas);

    return 0;
}
        