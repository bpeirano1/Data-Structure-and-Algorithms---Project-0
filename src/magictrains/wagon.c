#include "wagon.h"
#include <stdlib.h>
#include <stdio.h>



/** Inicializa una lista vacía */
List_Wagons* list_wagons_init()
{
  List_Wagons* list = calloc(1,sizeof(List_Wagons));
  list -> head = NULL;
  list -> tail = NULL;

  return list;
}

/** Inserta un nuevo elemento al final de la lista */
void list_wagons_append(List_Wagons* list, int capacity)
{
  
  Wagon* node = calloc(1,sizeof(Wagon));
  Passenger** wagon_seats = calloc(capacity,sizeof(Passenger*));

  node -> capacity = capacity;
  node -> busy_seats = 0;
  node -> seats = wagon_seats;
  node -> next = NULL;
  node -> prev = NULL;

  // Si la lista está vacía entonces queda como el primer elemento
  if(list -> head == NULL)
  {
    list -> head = node;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    list -> tail -> next = node;
    node -> prev = list -> tail;
  }
  // Luego se deja a este nodo como el último
  list -> tail = node;
}

void list_wagons_print(List_Wagons* list)
{
  for(Wagon* current = list -> head; current; current = current -> next)
  {
    printf("wagon capacity: %i | ", current -> capacity);
  }
}

/** Libera todos los recursos asociados a esta lista */
void list_wagons_destroy(List_Wagons* list)
{
  // Liberamos los nodos
  if(list -> head)
  {
    Wagon* curr = list -> head -> next;
    Wagon* prev = list -> head;

    while(curr)
    {
      free(prev);
      prev = curr;
      curr = curr -> next;
    }
    free(prev);
  }
  // Liberamos la lista en si
  free(list);
};