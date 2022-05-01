#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

typedef struct
{
    int TareaId; //Numerado en ciclo iterativo
    char *Descripcion;
    int duracion; //Entre 10 y 100
}Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
}typedef Nodo;

typedef struct Nodo* Lista;

//Declaracion de funciones
Lista crearLista();
int ingresaCantidad();
void cargarTareas(Lista *listaT, int cantidad_tareas);
Lista cargarTarea(Lista listaT, int ID);
void mostrarTareas(Lista listaT);
void mostrarTarea(Tarea tarea);
void consultaTareas(Lista *tareas_pendientes, Lista *tareas_realizadas);
void buscaTareaID(Lista *tareas_pendientes, Lista *tareas_realizadas, int ID);

int main()
{
    Lista tarea_pendiente  = crearLista();
    Lista tarea_realizada = crearLista();
    int cantidad = ingresaCantidad();

    printf("\n============================================\n");

    cargarTareas(&tarea_pendiente, cantidad);

    printf("\n============================================\n");

    mostrarTareas(tarea_pendiente);

    printf("\n============================================\n");

    consultaTareas(&tarea_pendiente, &tarea_realizada);

    printf("\n----------Mostrando tareas realizadas :)----------\n");
    mostrarTareas(tarea_realizada);

    printf("\n----------Mostrando tareas pendientes :(----------\n");
    mostrarTareas(tarea_pendiente);

    return 0;
}

Lista crearLista()
{
    return NULL;
}

int ingresaCantidad()
{
    int cant;

    do
    {
        printf("\n\nIngrese la cantidad de tareas que desea cargar:\n");
        scanf("%d", &cant);
        fflush(stdin);
    }while(cant<=0);

    return cant;
}

void cargarTareas(Lista *listaT, int cantidad)
{
    for(int i = 0; i < cantidad; i++)
    {
        *listaT = cargarTarea(listaT, i+1);

    }
}

Lista catgarTarea(Lista listaT, int ID)
{
    int duracionTarea;
    char *Buff;
    Buff = (char *)malloc(sizeof(char)*100);

    printf("Ingrese la descripcion de la tarea %d: ", ID);
    gets(Buff);

    do
    {
        printf("\nIngrese la duracion de la tarea (entre 10 y 100 horas):\n");
        scanf("%d", &duracionTarea);
        fflush(stdin);
    }while (duracionTarea<10 || duracionTarea>100);

    if(listaT!=NULL)
    {
        Lista aux = listaT;

        while (aux->siguiente!=NULL)
        {
            aux = aux->siguiente;
        }

        aux->siguiente = (Lista)malloc(sizeof(Nodo));

        aux->siguiente->T.duracion = duracionTarea;
        aux->siguiente->T.Descripcion = (char *)malloc(sizeof(Buff)+1);
        strcpy(aux->siguiente->T.Descripcion, Buff);
        aux->siguiente->T.TareaId = ID;

        aux->siguiente->siguiente = NULL;

        return listaT;
    }else
    {
        listaT = (Lista)malloc(sizeof(Nodo));

        listaT->T.TareaId = ID;
        listaT->T.duracion = duracionTarea;
        listaT->T.Descripcion = (char*)malloc(sizeof(Buff)+1);
        strcpy(listaT->T.Descripcion, Buff);

        listaT->siguiente = NULL;
        
        return listaT;
    }

    free(Buff);
    
}

void mostrarTareas(Lista listaT)
{
    while (listaT != NULL)
    {
        mostrarTarea(listaT->T);
        listaT = listaT->siguiente;
    }
}

void mostrarTarea(Tarea tarea)
{
    printf("\n-----Informacion de la tarea %d-----\n", tarea.TareaId);
    printf("* Id: %d\n", tarea.TareaId);
    printf("* Descripcion:");
    puts(tarea.Descripcion);
    printf("*Duracion: %s\n", tarea.duracion);
}

void consultaTareas(Lista *tareas_pendientes, Lista *tareas_realizadas)
{
    int respuesta;

    Lista listaPendientesAux = NULL;
    Nodo *proxNodoAux = NULL;

    printf("\n*****Revisando las tareas*****\n");

    while (*tareas_pendientes!=NULL)
    {
        proxNodoAux = (*tareas_pendientes)->siguiente;

        mostrarTarea((*tareas_pendientes)->T);

        do
        {
            printf("\nSe completo esta tarea? si:0 / no:1");
            scanf("%d", &respuesta);
            fflush(stdin);
        } while (respuesta !=0 || respuesta != 1);

        if(respuesta == 1)
        {
            (*tareas_pendientes)->siguiente = *tareas_realizadas;
            //El puntero del nodo a agregar a las tareas realizadas apunta al ultimo nodo que esa agregado en esta lista
            *tareas_realizadas = *tareas_pendientes;
            //La cabecera de tareas realizadas apunta al nodo de tareas pendientes donde se encuentra la tarea que quiero agregar
        }else
        {
            //En caso que no se haya realizado la tarea
            (*tareas_pendientes)->siguiente = listaPendientesAux;
            //El puntero del nodo a agregar a la lista auxiliar de tareas pendientes apuntara al ultimo nodo agregado en la lista de tareas pendientes original
            listaPendientesAux = *tareas_pendientes;
            //Con la lista auxiliar de tareas pendientes apunto al ultimo nodo de la lista original de tareas pendientes
        }

        *tareas_pendientes = proxNodoAux;
        //El puntero de tareas pendientes apunta al proximo nodo en la lista
        
    }
    
    *tareas_pendientes = listaPendientesAux;
}

