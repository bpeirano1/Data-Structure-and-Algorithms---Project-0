#include "passenger.h"
#include <stdlib.h>
#include <stdio.h>


/** Inicializa una lista vacía */
List_Passengers* list_passengers_init()
{
  List_Passengers* list = calloc(1,sizeof(List_Passengers));
  list -> head = NULL;
  list -> tail = NULL;

  return list;
}

/** Inserta un nuevo elemento al final de la lista */
void list_passengers_append(List_Passengers* list, int id, int destiny, int category)
{
  Passenger* node = calloc(1,sizeof(Passenger));
  node -> id = id;
  node -> destiny = destiny;
  node -> category = category;
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

/** Imprime todos los elementos de la lista */
void list_passengers_print(List_Passengers* list)
{
  for(Passenger* current = list -> head; current; current = current -> next)
  {
    printf("passenger: %i-%i\n", current -> id, current->destiny);
  }
}

/** Libera todos los recursos asociados a esta lista */
void list_passengers_destroy(List_Passengers* list)
{
  // Liberamos los nodos
  if(list -> head)
  {
    Passenger* curr = list -> head -> next;
    Passenger* prev = list -> head;

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