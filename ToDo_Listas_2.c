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
Lista insertaTareas(Lista tareas, int cantidad);
Tarea cargaTarea(int ID);
void mostrarTareas(Lista tareas); //Muestra todas las tareas pertenecientes a una lista
void mostrarTarea(Tarea tarea); //Muestra una tarea en particular (sirve al consultar una a una las tareas)
Lista consultaTareas(Lista tareas, Lista tareas_real,int cantidad);

int main()
{
    int cantidad = ingresaCant();
    Lista tareasPendientes = crearLista();
    Lista tareasRealizadas = crearLista();

    tareasPendientes = insertaTareas(tareasPendientes, cantidad);
    //Carga de tareas a la lista

    mostrarTareas(tareasPendientes);


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

Lista insertaTareas(Lista tareas, int cantidad)
{
    printf("\n*****Ingreso las tareas*****\n");
    for(int i = 0; i < cantidad; i++)
    {
        Lista nuevo = (Lista)malloc(sizeof(Nodo));
        nuevo->T = cargaTarea(i+1);
        nuevo->siguiente = tareas;
        tareas = nuevo;
        printf("\n=============================================================\n");
    }
    return tareas;
}

Tarea cargaTarea(int ID)
{
    Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea)); 
    //Reserva dinamica para la tarea que se va a ingresar
    char *Buff = (char *)malloc(sizeof(char)*100);
    //Reserva dinamica para ingresar la descripcion de la tarea
    
    nuevaTarea->TareaID = ID;

    printf("\nIngrese la descripcion de la tarea %d: ", ID);
    gets(Buff);
    fflush(stdin);

    nuevaTarea->Descripcion = (char *)malloc(sizeof(Buff)+1);
    //Reserva dinamica del espacio necesario para almacenar la descripcion
    strcpy(nuevaTarea->Descripcion, Buff);
    free(Buff);

    do
    {
        printf("\nIngrese la demora que tendra en concluir la tarea (entre 10 y 100 horas): ");
        scanf("%d", &nuevaTarea->duracion);
        fflush(stdin);
    } while (nuevaTarea->duracion < 10 || nuevaTarea->duracion > 100);

    return *nuevaTarea;

}

void mostrarTareas(Lista tareas)
{
    struct Nodo *seguidor = tareas;
    printf("\n------Tareas a realizar :(------\n");
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

Lista consultaTareas(Lista tareas, Lista tareas_real,int cantidad)
{
    int respuesta;
    Lista seguidor = tareas;
    Lista seguidorAux;

    for(int i = 0; i < cantidad; i++)
    {
        do
        {
            mostrarTarea(seguidor->T);

            printf("\n¿Se completo esta tarea? Si:0 / No:1");
            scanf("%d", &respuesta);
            fflush(stdin);
        } while (respuesta != 0 || respuesta != 1);
        
        if(respuesta == 0)
        {
            

            seguidor = seguidor->siguiente;

        }

        seguidor = seguidor->siguiente;
    }
}