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
    Nodo *siguiente;
};

typedef struct Nodo* Nodo;

//Declaracion de funciones

int main()
{
    return 0;
}