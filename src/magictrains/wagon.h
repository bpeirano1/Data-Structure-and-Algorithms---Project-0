#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "passenger.h"

#pragma once

// Declaramos el struct para un nodo de la lista
struct wagon;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct wagon Wagon;

// Definimos el struct nodo
struct wagon
{
  /** El valor que guarda el nodo */

  int capacity;
  int busy_seats;
  //cambiar por una arreglo de asientos
  Passenger** seats; 
  /** Un puntero al siguiente nodo de la lista */
  Wagon* next;
  Wagon* prev;
};


// Declaramos el struct para la lista
struct linked_list_wagons;
// Definimos un alias para el struct lista
typedef struct linked_list_wagons List_Wagons;

// Definimos el struct lista
struct linked_list_wagons
{
  /** El primer nodo de la lista */
  Wagon* head;
  /** El último nodo de la lista */
  Wagon* tail;
};

// Declaramos las funciones asociadas

/** Inicializa una lista vacía */
List_Wagons* list_wagons_init();
/** Inserta un nuevo elemento al final de la lista */
void list_wagons_append(List_Wagons* list, int capacity);
/** Imprime todos los elementos de la lista */
void list_wagons_print(List_Wagons* list);
// /** Libera todos los recursos asociados a esta lista */
void wagon_seats_print(Passenger** seats, int length_seats);
void list_wagons_destroy(List_Wagons* list);
