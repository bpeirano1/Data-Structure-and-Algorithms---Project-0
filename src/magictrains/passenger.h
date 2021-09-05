#pragma once

// Declaramos el struct para un nodo de la lista
struct passenger;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct passenger Passenger;

// Definimos el struct nodo
struct passenger
{
  /** El valor que guarda el nodo */
  int id;
  int destiny;
  int category;
  /** Un puntero al siguiente nodo de la lista */
  Passenger* next;
  Passenger* prev;
};

// Declaramos el struct para la lista
struct linked_list_passengers;
// Definimos un alias para el struct lista
typedef struct linked_list_passengers List_Passengers;

// Definimos el struct lista
struct linked_list_passengers
{
  /** El primer nodo de la lista */
  Passenger* head;
  /** El último nodo de la lista */
  Passenger* tail;
};

// Declaramos las funciones asociadas

/** Inicializa una lista vacía */
List_Passengers* list_passengers_init();
/** Inserta un nuevo elemento al final de la lista */
void list_passengers_append(List_Passengers* list, int id, int destiny, int category);
/** Imprime todos los elementos de la lista */
void list_passengers_print(List_Passengers* list);
/** Libera todos los recursos asociados a esta lista */
void list_passengers_destroy(List_Passengers* list);