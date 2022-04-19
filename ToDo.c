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
//typedef struct Tarea Tarea;

//Declaracion de funciones
void ingresaCantidadTareas();
void cargaTareas(Tarea **arr_tareas, int cantidad);
void mostrar(Tarea **arr_tareas);

int main()
{
    ingresaCantidadTareas();
    return 0;
}

void ingresaCantidadTareas()
{
    int cant_tareas;
    Tarea **arr_tareas;

    printf("\nIngrese la cantidad de tareas a cargar: ");
    scanf("%d",&cant_tareas);
    fflush(stdin);
    
    arr_tareas = (Tarea **)malloc(sizeof(Tarea)*cant_tareas);

    cargaTareas(arr_tareas, cant_tareas);
}

void cargaTareas(Tarea **arr_tareas, int cantidad)
{
    int i;
    char *Buff = (char *)malloc(sizeof(char)*100);
    
    //Tarea tareas;
    for(i=0;i<cantidad; i++)
    {
        arr_tareas[i] = (Tarea *)malloc(sizeof(Tarea));

        arr_tareas[i]->TareaId = i+1;
        printf("Descripcion de la tarea %d: ",i+1);
        gets(Buff);
        fflush(stdin);
        arr_tareas[i]->Descripcion = (char *)malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(arr_tareas[i]->Descripcion, Buff);
        arr_tareas[i]->duracion = rand()%101 + 10;

        // = tareaParticular;
        //free(tareaParticular->Descripcion);
        //arr_tareas[i]->TareaId = i+1;
        //

        //strcpy(arr_tareas[i]->Descripcion, Buff);

        //arr_tareas[i]->duracion = rand()%101 + 10;
        //free(arr_tareas[i]->Descripcion);
    }
    free(Buff);
    mostrar(arr_tareas);
}

void mostrar(Tarea **arr_tareas)
{
    int i;
    printf("\n-----------Tareas a realizar :)-----------\n");
    for(i=0; i<sizeof(arr_tareas);i++)
    {
        printf("Id tarea: %d",arr_tareas[i]->TareaId);
        printf("\nDescripcion: %s",arr_tareas[i]->Descripcion);
        printf("\nDuracion: %d hs",arr_tareas[i]->duracion);
        printf("\n");
        free(arr_tareas[i]->Descripcion);
    }
    free(arr_tareas);
}