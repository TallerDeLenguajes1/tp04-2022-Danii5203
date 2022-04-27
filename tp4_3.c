#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Creamos las estructuras
typedef struct
{
    int TareaID;
    char *descripcion;
    int duracion;
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo* Siguiente;
}Nodo;

//funciones
Nodo * crearTarea(char *descripcionEntrada, int id, int duracion);
Nodo * insertarTareaAlFinal(Nodo * listaTareas, Nodo * nuevaTarea);
void mostrarTareas(Nodo * tarea, int id);
Nodo * cargarTareasRealizadas(Nodo * tareasPendientes, Nodo * tareasRealizadas, int id, int cantTareas);
Nodo * borrarNodo(Nodo * lista, int id, int cantTareas);

void liberarMemoria(Nodo * lista);


int main(){
    srand(time(NULL)); //Instrucción que inicializa el generador de números aleatorios

    //Pedimos la cantidad de tareas
    int cantTareas;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);
    printf("\n");

    //Puntero auxiliar para cargar la descripcion
    char *buff;
    buff = (char *) malloc(sizeof(char) * 100);

    //Creamos una lista que apuntara a NULL al principio
    Nodo * tareasPendientes = NULL;
    Nodo * tareasRealizadas = NULL;

    //Cargo las tareas pendientes
    int entradaDuracion;
    for(int i=0; i<cantTareas; i++){ //pediremos la descripcion y duracion de la tarea
        printf("Ingrese una descripcion de la tarea %d: ", i+1);
        fflush(stdin);
        gets(buff);
        fflush(stdin);
        do //controlamos que la duracion este entre 10 y 100
        {
            printf("Ingrese la duracion: ");
            scanf("%d", &entradaDuracion);
        } while (entradaDuracion<10 || entradaDuracion>100);
        printf("\n");
        
        Nodo * nuevaTarea = crearTarea(buff, i+1, entradaDuracion); //recibimos la tarea q creamos
        tareasPendientes = insertarTareaAlFinal(tareasPendientes, nuevaTarea); //recibimos la lista con el nodo nuevo insertado en el final
    }

    //Cargamos las tareas realizadas
    Nodo * listaAux = tareasPendientes;
    char respuesta; //aqui guardaremos la respuesta de si realizo o no la tarea
    for(int i=1; i<cantTareas+1; i++){
        if(listaAux != NULL){
            printf("\nRealizo la tarea %d?(Descripcion: %s)\n- (Y / N): ", listaAux->T.TareaID, listaAux->T.descripcion);
            fflush(stdin);
            scanf("%c", &respuesta);
            fflush(stdin);
            printf("\n");

            if(respuesta == 'Y' || respuesta == 'y'){
                tareasRealizadas = cargarTareasRealizadas(tareasPendientes, tareasRealizadas, listaAux->T.TareaID, cantTareas); //mandamos a cargar la tarea realizada
                tareasPendientes = borrarNodo(tareasPendientes, listaAux->T.TareaID, cantTareas); //borramos la tarea que ya realizamos
                cantTareas = cantTareas - 1; //restamos a la cant. de tareas pendientes la tarea que acabamos de borrar
                i = i-1; //y retrocedemos una posicion para preguntar sobre la tarea que se puso en la posicion de la que ya borramos
            }
        }else{
            printf("\nNo hay tareas.\n");
        }
        listaAux = listaAux->Siguiente; //avanzamos en la lista de tareas pendientes
    }

    //Mostramos las tareas pendientes y realizadas
    listaAux = tareasPendientes;
    printf("\n------------------ Tareas pendientes ------------------\n");
    while(listaAux != NULL){
        mostrarTareas(listaAux, listaAux->T.TareaID);
        listaAux = listaAux->Siguiente;
    }
    printf("\n------------------ Tareas realizadas ------------------\n");
    listaAux = tareasRealizadas;
    while(listaAux != NULL){
        mostrarTareas(listaAux, listaAux->T.TareaID);
        listaAux = listaAux->Siguiente;
    }
    printf("\n");
    
    
    //Liberamos memoria
    free(buff);
    free(listaAux);
    liberarMemoria(tareasPendientes);
    liberarMemoria(tareasRealizadas);

   return 0;
}

//Funcion para crear un nuevo nodo
Nodo * crearTarea(char *descripcionEntrada, int id, int duracion){
    Nodo * tareaAux = (Nodo *) malloc(sizeof(Nodo)); //reservamos memoria para crear nuestro nodo
    tareaAux->T.TareaID = id;
    tareaAux->T.descripcion = (char *) malloc(sizeof(char) * (strlen(descripcionEntrada)+1)); //reservamos memoria en el nodo para cargar la descripcion
    strcpy(tareaAux->T.descripcion, descripcionEntrada);
    tareaAux->T.duracion = duracion;
    tareaAux->Siguiente = NULL; //hacemos que el nodo apunte a NULL por precaucion 
}

//Funcion para insertar un nodo al final de la lista
Nodo * insertarTareaAlFinal(Nodo * listaTareas, Nodo * nuevaTarea){
    Nodo * listaAux = listaTareas;

    if(listaAux != NULL){ //si la lista de tareas no esta vacia
        while(listaAux->Siguiente != NULL){ //recorre la lista hasta que encuentre un nodo cuyo nodo siguiente sea un NULL
            listaAux = listaAux->Siguiente; //se va moviendo de nodo
        }
        listaAux->Siguiente = (Nodo *) malloc(sizeof(Nodo));
        listaAux->Siguiente = nuevaTarea; //agregamos el nodo creado al final de la lista

        return listaTareas;
    }else{ //si la lista si esta vacia
        listaAux = nuevaTarea; //inserto el primer nodo de la lista

        return listaAux;
    }
}

//Funcion para mostrar tareas
void mostrarTareas(Nodo * tarea, int id){
    printf("\n----- Tarea %d -----\n", id);
    printf("ID: %d\n", tarea->T.TareaID);
    printf("Descripcion: %s\n", tarea->T.descripcion);
    printf("Duracion: %d\n", tarea->T.duracion);
}

//Cargamos las tareas realizadas
Nodo * cargarTareasRealizadas(Nodo * tareasPendientes, Nodo * tareasRealizadas, int id, int cantTareas){
    Nodo * listaAuxPendientes = tareasPendientes;
    Nodo * listaAuxRealizadas = tareasRealizadas;

    //Verificamos las siguientes condiciones
    while(listaAuxPendientes != NULL)
    {
        if(listaAuxPendientes->T.TareaID == id)
        {
            if(listaAuxRealizadas != NULL)
            {
                while(listaAuxRealizadas->Siguiente != NULL) //se mueve al ultimo nodo con datos que tenemos en la lista de tareas realizadas
                {
                    listaAuxRealizadas = listaAuxRealizadas->Siguiente;
                }
                listaAuxRealizadas->Siguiente = crearTarea(listaAuxPendientes->T.descripcion, id, listaAuxPendientes->T.duracion); //cargamos la nueva tarea en el final de la lista

                return tareasRealizadas;
                
            }else{
                listaAuxRealizadas = crearTarea(listaAuxPendientes->T.descripcion, id, listaAuxPendientes->T.duracion); //cargamos la lista en el inicio

                return listaAuxRealizadas;
            }
        }
        listaAuxPendientes = listaAuxPendientes->Siguiente;
    }

}

//Borrar un nodo de una lista 

//CAOSSSSSSSSSS!!!!!!!!!!
Nodo * borrarNodo(Nodo * lista, int id, int cantTareas){
    Nodo * listaAux = lista;
    Nodo * borradoNodo = lista;
    Nodo * inicioLista = lista;

    int salir=0; //Nos permitira salir del while cuando borremos una tarea
    while(borradoNodo != NULL && salir != 1)
    {
        if(borradoNodo->T.TareaID == id){ //si en tareas pendientes encuentra la tarea que ya realizamos
            listaAux = borradoNodo->Siguiente; //apuntamos a la tarea que estaba despues de la realizada con una lista aux
            borradoNodo = NULL; //Nuleamos la tarea que realizamos
            salir=1; //salimos del whuile
        }
        else //si no la encuentra
        {
            borradoNodo = borradoNodo->Siguiente; //nos movemos a la siguiente
            listaAux = listaAux->Siguiente; //nos movemos a la siguiente
        }
    }


    //En este while obtendremos la lista hasta la tarea antes de la cual borramos
    while(inicioLista->Siguiente!=NULL && inicioLista->Siguiente->T.TareaID!=id && id>1){
        inicioLista = inicioLista->Siguiente;
    }

    if(id>1){
        inicioLista->Siguiente = listaAux; //apuntamos desde la tarea anterior a la que borramos a la que estaba despues de la que borramos
    }
    else //en caso de que borraramos la primera tarea de la lista
    {
        inicioLista = listaAux; //apuntamos hacia la segunda tarea
        lista = inicioLista;
    }

    return lista; //devolvemos la lista
}

//Liberamos memoria
void liberarMemoria(Nodo * lista){
    Nodo * Aux; //Aux. que servira para apuntar a la lista para no perder la referencia
    while(lista!=NULL){
        Aux=lista; //asignamos la lista en el nodo que lo dejamos
        lista=lista->Siguiente; //pasamos al siguiente nodo
        free(Aux->T.descripcion); //Liberamos el espacio que pedimos para guardar la descripcion
        free(Aux); //liberamos el nodo  
    } 
}