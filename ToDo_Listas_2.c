#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<stdlib.h>

typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int duracion;
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
}Nodo;

typedef struct Nodo* Lista;

//Declaracion de funciones
int ingresaCant();
Lista crearLista();
void insertaTareas(Lista *tareas, int cantidad);
Lista cargaTarea(Lista tareas, int ID);
void mostrarTareas(Lista tareas); //Muestra todas las tareas pertenecientes a una lista
void mostrarTarea(Tarea tarea); //Muestra una tarea en particular (sirve al consultar una a una las tareas)
void consultaTareas(Lista *tareas, Lista *tareas_realizadas);
void estadoTareas(Lista tareas, Lista tareas_realizadas);
void buscaTareaID(Lista tareas, int ID);
void buscaTareaPalabra(Lista tareas, char* palabra);
void liberarMemoria(Lista *tareas);

int main()
{
    int cantidad = ingresaCant();
    int busca_ID;
    char* buscaPalabra;
    Lista tareasPendientes = crearLista();
    Lista tareasRealizadas = crearLista();

    insertaTareas(&tareasPendientes, cantidad);
    //Carga de tareas a la lista
    printf("\n------Tareas a realizar :(------\n");
    mostrarTareas(tareasPendientes);
    
    printf("\n************************************Compruebo las tareas realizadas************************************\n");
    consultaTareas(&tareasPendientes, &tareasRealizadas);

    estadoTareas(tareasPendientes, tareasRealizadas);

    do
    {
        printf("\nIngrese el ID de la tarea que dese buscar: \n--> ");
        scanf("%d", &busca_ID);
        fflush(stdin);
    } while (busca_ID <= 0 || busca_ID > cantidad);

    printf("\n========Busqueda de la tarea con ID %d en tareas pendientes========\n", busca_ID);
    buscaTareaID(tareasPendientes, busca_ID);

    printf("\n========Busqueda de la tarea con ID %d en tareas realizadas========\n", busca_ID);
    buscaTareaID(tareasRealizadas, busca_ID);

    printf("\n\n==> Ingrese la palabra a buscar en las listas:\n");
    gets(buscaPalabra);
    fflush(stdin);

    printf("\n========Busqueda de la tarea con la palabra (%s) en tareas pendientes========\n", buscaPalabra);
    buscaTareaPalabra(tareasPendientes, buscaPalabra);

    printf("\n========Busqueda de la tarea con la palabra (%s) en tareas realizadas========\n", buscaPalabra);
    buscaTareaPalabra(tareasRealizadas, buscaPalabra);

    liberarMemoria(&tareasPendientes);
    liberarMemoria(&tareasRealizadas);

/*  
    printf("\n-------Muestra de tareas Pendientes-------\n");
    mostrarTareas(tareasPendientes);

    printf("\n-------Muestra de tareas Realizadas-------\n");
    mostrarTareas(tareasRealizadas);
*/

    return 0;
}

int ingresaCant()
{
    int cant = 0;
    do
    {
        printf("\nIngrese la cantidad de tareas que debe realizar:");
        scanf("%d", &cant);
        fflush(stdin);
    } while (cant<=0);
    return cant;
}

Lista crearLista()
{
    return NULL; //Al inicializar la cabeza apunta a un null
}

void insertaTareas(Lista *tareas, int cantidad)
{
    printf("\n*****Ingreso las tareas*****\n");
    for(int i = 0; i < cantidad; i++)
    {
        *tareas = cargaTarea(*tareas, i+1);
        
        /*
        Lista nuevo = (Lista *)malloc(sizeof(Nodo));
        nuevo.T = cargaTarea(i+1);
        nuevo.siguiente = tareas;
        tareas = nuevo;*/
        printf("\n=============================================================\n");
    }
    //return tareas;
}

Lista cargaTarea(Lista tareas, int ID)
{
    //Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea)); 
    //Reserva dinamica para la tarea que se va a ingresar
    
    char *Buff = (char *)malloc(sizeof(char)*100);
    //Reserva dinamica para ingresar la descripcion de la tarea
    int duracion;
    //nuevaTarea->TareaID = ID;

    printf("\nIngrese la descripcion de la tarea %d: ", ID);
    gets(Buff);
    fflush(stdin);

    //nuevaTarea->Descripcion = (char *)malloc(sizeof(Buff)+1);
    //Reserva dinamica del espacio necesario para almacenar la descripcion
    //strcpy(nuevaTarea->Descripcion, Buff);
    //free(Buff);

    do
    {
        printf("\nIngrese la demora que tendra en concluir la tarea (entre 10 y 100 horas): ");
        scanf("%d", &duracion);
        fflush(stdin);
    } while (duracion < 10 || duracion > 100);

    if(tareas != NULL)
    {
        //En caso que ya se hayan ingresado tareas
        Lista auxiliar = tareas;

        while (auxiliar->siguiente != NULL) 
        {
            auxiliar = auxiliar->siguiente;
        }
        //Como al ingresar a una lista cargada estaremos en la cabecera de la misma
        //debemos ir recorriendola hasta encontrarnos con el nodo cuyo siguiente es null

        auxiliar->siguiente = (Lista)malloc(sizeof(Nodo));
        //Como estoy en la "cabecera" de la lista, en un nodo ya cargado, hago la
        //reserva dinamica del nodo siguiente y luego lo cargo

        auxiliar->siguiente->T.Descripcion = (char*)malloc(sizeof(Buff)+1);
        //Reserva dinamica para la descripcion
        strcpy(auxiliar->siguiente->T.Descripcion, Buff);

        auxiliar->siguiente->T.duracion = duracion;
        auxiliar->siguiente->T.TareaID = ID;
        auxiliar->siguiente->siguiente = NULL;
        //Entonces avanzo dos posiciones al nodo en el que estoy y le doy valor NULL
        return tareas;
    }else
    {
        //En caso que la lista este vacia (caso 0)
        tareas = (Lista)malloc(sizeof(Nodo));

        tareas->T.TareaID = ID;
        tareas->T.duracion = duracion;
        tareas->T.Descripcion = (char*)malloc(sizeof(Buff)+1);
        //Reserva dinamica para la descripcion
        strcpy(tareas->T.Descripcion, Buff);
        tareas->siguiente = NULL;
        //Como me encuentro en el primer nodo agregado a la lista el siguiente sera null
        return tareas;
    }
    //return *nuevaTarea;
    free(Buff);
}

void mostrarTareas(Lista tareas)
{
    struct Nodo *seguidor = tareas;
    while (seguidor != NULL)
    {
        printf("\n--> Tarea ID: %d", seguidor->T.TareaID);
        printf("\n--> Descripcion tarea: %s", seguidor->T.Descripcion);
        printf("\n--> Duracion: %d hs", seguidor->T.duracion);
        seguidor = seguidor->siguiente;
        printf("\n-------------------------------------------------------------\n");
    }
}

void mostrarTarea(Tarea tarea)
{
    printf("\n----Datos de la tarea: %d----\n", tarea.TareaID);
    printf("\n--> Tarea ID: %d", tarea.TareaID);
    printf("\n--> Descripcion tarea: %s", tarea.Descripcion);
    printf("\n--> Duracion: %d hs", tarea.duracion);
}

void consultaTareas(Lista *tareas, Lista *tareas_realizadas)
{
    int respuesta;
    //Lista seguidor = tareas;
    Lista listaTareasAux = NULL;
    Nodo *nodoAux = NULL;

    //for(int i = 0; i < cantidad; i++)
    while( *tareas != NULL)
    {
        //Ingreso en la cabeza de la lista
        nodoAux = (*tareas)->siguiente;
        mostrarTarea((*tareas)->T);

        do
        {
            printf("\n¿Se completo esta tarea? Si:0 / No:1 \n-->");
            scanf("%d", &respuesta);
        } while (respuesta != 0 && respuesta != 1);
        
        if(respuesta == 0)
        {
            (*tareas)->siguiente = *tareas_realizadas;
            //Paso por punteros

            *tareas_realizadas = *tareas;
            //El puntero de la cabecera de la lista de las tareas realizadas apuntara al nodo recien agregado
            
            
            //seguidor = nodoAux;
            //La cabecera de la lista tareas apuntara al siguiente nodo en la lista?
        }else
        {
            (*tareas)->siguiente = listaTareasAux;
            listaTareasAux = *tareas;
        }
        *tareas = nodoAux;
    }
    *tareas = listaTareasAux;
    //Vuelvo a la cabecera de las tareas pendientes

    //return *tareas_realizadas;
}

void estadoTareas(Lista tareas, Lista tareas_realizadas)
{
    printf("\n-------Muestra de tareas Pendientes-------\n");
    mostrarTareas(tareas);

    printf("\n-------Muestra de tareas Realizadas-------\n");
    mostrarTareas(tareas_realizadas);
}

void buscaTareaID(Lista tareas, int ID)
{
    struct Nodo *auxiliar = tareas;
    printf("\n++++++Busqueda de tarea con ID: %d++++++\n", ID);
    while (auxiliar != NULL)
    {
        if(auxiliar->T.TareaID == ID)
        {
            printf("\n--> Tarea encontrada:\n");
            mostrarTarea(auxiliar->T);
            printf("\n");
        }
        auxiliar = auxiliar->siguiente;
    }
}

void buscaTareaPalabra(Lista tareas, char *palabra)
{
    struct Nodo* auxiliar = tareas;
    //printf("\n++++++Busqueda de tarea con palabra: %s en su descripcion++++++\n", palabra);
    while (auxiliar!=NULL)
    {
        if(strstr(auxiliar->T.Descripcion, palabra)!=NULL)
        {
            printf("\n--> Tarea encontrada:\n");
            mostrarTarea(auxiliar->T);
            printf("\n");
        }
        auxiliar = auxiliar->siguiente;
    }
    
}

void liberarMemoria(Lista* tareas){
    Nodo* auxLiberarMemoria = NULL;
    while(tareas){
        free((*tareas)->T.Descripcion);
        auxLiberarMemoria = *tareas;
        *tareas = (*tareas)->siguiente;
        free(auxLiberarMemoria);
    }
}