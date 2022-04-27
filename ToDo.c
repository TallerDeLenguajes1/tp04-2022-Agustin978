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
int ingresaCantidadTareas();
void cargaTareas(Tarea **arr_tareas, int cantidad);
void mostrarTarea(Tarea tarea);
//void mostrar(Tarea **arr_tareas);
int consultaTareas(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad);
void estadoTareas(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad, int completadas);
void buscaTareaID(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad, int completadas);


int main()
{
    Tarea **arr_tareas;
    printf("===========================================");
    int cant = ingresaCantidadTareas();
    printf("===========================================");
    
    arr_tareas = (Tarea **)malloc(sizeof(Tarea *)*cant);

    cargaTareas(arr_tareas, cant);
    //Se genera el arreglo de manera dinamica con respecto a la cantidad de tareas que se cargaran en el
    
    printf("\n-----------Tareas a realizar :)-----------\n");
    for(int i = 0; i < cant; i++)
    {
        mostrarTarea(*arr_tareas[i]);
    }

    printf("===========================================");

    Tarea **arr_tareasRealizadas;
    arr_tareasRealizadas = (Tarea **)malloc(sizeof(Tarea *)*cant);
    //Genera arreglo del mismo tamaño que el anterior, donde se almacenaran las tareas ya realizadas
    
    int completadas = consultaTareas(arr_tareas, arr_tareasRealizadas, cant);

    printf("===========================================");

    estadoTareas(arr_tareas, arr_tareasRealizadas, cant, completadas);

    printf("===========================================");

    buscaTareaID(arr_tareas, arr_tareasRealizadas, cant, completadas);

    return 0;
}


int ingresaCantidadTareas()
{
    int cant_tareas;
    
    do
    {
        printf("\nIngrese la cantidad de tareas a cargar: ");
        scanf("%d",&cant_tareas);
        fflush(stdin);
    } while (cant_tareas<=0);
    
    return cant_tareas;
}

void cargaTareas(Tarea **arr_tareas, int cantidad)
{
    char *Buff = (char *)malloc(sizeof(char)*100);
    
    //Tarea tareas;
    for(int i = 0 ; i < cantidad ; i++)
    {
        printf("\n*************************************\n");
        arr_tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        //Almaceno un espacio de memoria dinamica para los elementos de cada tarea

        arr_tareas[i]->TareaId = i+1;
        printf("\nDescripcion de la tarea %d:\n",i+1);
        gets(Buff);
        fflush(stdin);

        arr_tareas[i]->Descripcion = (char *)malloc((strlen(Buff)+1));
        //Almaceno un espacio en memoria para guardar la descripcion de la tarea
        strcpy(arr_tareas[i]->Descripcion, Buff);
        
        do
        {
            printf("\nIngrese la duracion de la tarea a realizar (entre 10 y 100 horas):\n");
            scanf("%d", &(arr_tareas[i]->duracion));
            fflush(stdin);
        } while (arr_tareas[i]->duracion < 10 || arr_tareas[i]->duracion > 100);
    }
    free(Buff);
    //mostrar(arr_tareas);
}

void mostrarTarea(Tarea tarea)
{
    printf("-----Informacion de la tarea %d-----\n", tarea.TareaId);
    printf("* ID: %d\n", tarea.TareaId);
    printf("* Descripcion:");
    puts(tarea.Descripcion);
    printf("* Duracion: %d\n", tarea.duracion);
}

int consultaTareas(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad)
{
    int respuesta;
    //char *r_1="S", *r_2="s", *r_3="N", *r_4="n";
    int realizadas=0;
    printf("\n-------------------------------------\n");
    printf("Revisando tareas relizadas:\n");
    for(int i = 0; i < cantidad; i++)
    {
        mostrarTarea(*arr_tareas[i]);
        
        do
        {
            printf("¿Se realizo esta tarea? Si:0 o No:1 \n");
            scanf("%d", &respuesta);
            fflush(stdin);
        } while(respuesta!=0 && respuesta !=1);
        //while (strcmp(&respuesta,r_1)!=0 || strcmp(&respuesta,r_2)!=0 || strcmp(&respuesta,r_3)!=0 || strcmp(&respuesta,r_4)!=0);
        
        //if(strcmp(&respuesta,r_1)==0 || strcmp(&respuesta,r_2)==0)
        if (respuesta==0)
        {
            arr_tareasRealizadas[realizadas] = arr_tareas[i];
            arr_tareas[i] = NULL; 
            //Como paso la tarea realizada a un nuevo arreglo, coloco en la posicion donde se encontraba esta un NULL
            realizadas++;
        }

    }
    return realizadas;
}

void estadoTareas(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad, int completadas)
{
    printf("\n----------Tareas completadas----------\n");
    for(int i = 0; i < completadas; i++)
    {
        mostrarTarea(*arr_tareasRealizadas[i]);
    }
    printf("\n----------Tareas incompletas :(----------\n");
    for(int j = 0; j < cantidad; j++)
    {
        if(arr_tareas[j]!=NULL)
        {
            mostrarTarea(*arr_tareas[j]);
        }
    }
}

void buscaTareaID(Tarea **arr_tareas, Tarea **arr_tareasRealizadas, int cantidad, int completadas)
{
    int ID_buscar;
    printf("\n\n----------------------------------------------------\n");
    do
    {
        printf("\nIngrese el Id de la tarea que desea buscar:\n");
        scanf("%d", &ID_buscar);
        fflush(stdin);
    } while (ID_buscar<0);
    
    for(int i = 0; i < completadas; i++)
    {
        if(arr_tareasRealizadas[i]->TareaId == ID_buscar)
        {
            mostrarTarea(*arr_tareasRealizadas[i]);
            printf("\n-Tarea ya completada :)");
        }
    }

    for (int j = 0; j < cantidad; j++)
    {
        if(arr_tareas[j] != NULL && arr_tareas[j]->TareaId == ID_buscar)
        {
            mostrarTarea(*arr_tareas[j]);
            printf("\n-Tarea sin completar aun :(");
        }
    }
    
}
