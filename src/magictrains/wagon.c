#include "wagon.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/** Inicializa una lista vacía */
List_Wagons* list_wagons_init()
{
  List_Wagons* list = calloc(1,sizeof(List_Wagons));
  list -> head = NULL;
  list -> tail = NULL;

  return list;
}

/** Inserta un nuevo elemento al final de la lista */
void list_wagons_append(List_Wagons* list, int capacity, int id)
{
  Passenger** wagon_seats = calloc(capacity,sizeof(Passenger*));
  for (int i = 0; i < capacity; i++)
  {
    Passenger* seat = calloc(1,sizeof(Passenger));
    seat -> id = 0;
    seat -> destiny = 0;
    seat -> category = 0;
    seat -> in_seat = 0;
    seat -> next = NULL;
    wagon_seats[i]=seat;
  };

  Wagon* node = calloc(1,sizeof(Wagon));
  node -> capacity = capacity;
  node -> busy_seats = 0;
  node -> seats = wagon_seats;
  node -> next = NULL;
  node -> id = id;
  // node -> prev = NULL;

  // Si la lista está vacía entonces queda como el primer elemento
  if(list -> head == NULL)
  {
    list -> head = node;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    list -> tail -> next = node;
    // node -> prev = list -> tail;
  }
  // Luego se deja a este nodo como el último
  list -> tail = node;
}

void list_wagons_fprint(List_Wagons* list, FILE* output_file)
{
  for(Wagon* current = list -> head; current; current = current -> next)
  {
    wagon_seats_fprint(current->seats, current -> capacity, output_file);
    fprintf(output_file," |");
  };
}

void wagon_seats_fprint(Passenger** seats, int length_seats, FILE* output_file){
  for (int i=0; i<length_seats; i++){
    if (seats[i]->in_seat){
      fprintf(output_file," %d-%d",seats[i]->id,seats[i]->destiny);
    }
    else {
      fprintf(output_file," X");
    };
    
  }
}


void list_wagons_print(List_Wagons* list){
  for(Wagon* current = list -> head; current; current = current -> next)
  {
    wagon_seats_print(current->seats, current -> capacity);
    printf(" |");
  };
}

void wagon_seats_print(Passenger** seats, int length_seats){
  for (int i=0; i<length_seats; i++){
    if (seats[i]->in_seat){
      printf(" %d-%d",seats[i]->id,seats[i]->destiny);
    }
    else {
      printf(" X");
    };
    
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


void wagon_add_person(Wagon* wagon ,Passenger* passenger, int train_id){

  int asiento_encontrado = 0;
  

  for (int i=0; i < wagon -> capacity; i++){
    if (!wagon->seats[i]->in_seat && !asiento_encontrado){
      wagon->seats[i]->id = passenger->id;
      wagon->seats[i]->destiny = passenger->destiny;
      wagon->seats[i]->category = passenger->category;
      wagon->seats[i]->next = passenger->next;
      wagon->seats[i]->in_seat = 1;
      asiento_encontrado = 1;
      wagon->busy_seats += 1;
      return;  
    };
    
  };
  printf("Error agregando persona al vagon pasajero: %d-%d-%d\n", passenger->id,passenger->destiny,passenger->category);
};

void list_separated_wagons_append(List_Wagons* list, Wagon* node)
{
  if(list -> head == NULL)
  {
    list -> head = node;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    list -> tail -> next = node;
    // node -> prev = list -> tail;
  }
  // Luego se deja a este nodo como el último
  list -> tail = node;
}

void list_original_separated_destroy(List_Wagons* list){
  list->head=NULL;
  list->tail=NULL;
  free(list);
}
