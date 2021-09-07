#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "station.h"
#include "platform.h"
#include "passenger.h"
#include "train.h"



/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");


  /* Leemos la cantidad de estaciones y andenes por estación*/
  int N_STATIONS;
  fscanf(input_file, "%d", &N_STATIONS);

  //Creo las estaciones
  Station** stations = stations_init(N_STATIONS);
  
  int N_PLATFORMS;
  for (int s = 0; s < N_STATIONS; s++)
  {
    fscanf(input_file, "%d", &N_PLATFORMS);
    /*  [Por implementar] Creamos los andenes con la cantidad de andenes dada */

    Platform** platforms = platforms_init(N_PLATFORMS);
    stations[s] -> n_platform = N_PLATFORMS;
    stations[s] -> platforms=platforms;
  };

  //Ahora creamos un contador para los pasajeros: 
  int passengers_count = 0;
  int trains_count = 0;

  /* String para guardar la instrucción actual*/
  char command[32];

  /* Leemos la primera instrucción */
  fscanf(input_file, "%s", command);

  /* Mientras la instrucción sea distinta a END */
  while(!string_equals(command, "END"))
  {
    /* [Por implementar] A continuación debes implementar cada evento */
    if (string_equals(command, "NUEVO-TREN"))
    {
      int station_id, platform_id, length, seats;
      fscanf(input_file, "%d %d %d", &station_id, &platform_id, &length);

      Train* new_train = train_init(trains_count, station_id, platform_id, length);
      trains_count++;

      int total_train_capacity = 0;

      for (int l = 0; l < length; l++)
      {
        fscanf(input_file, "%d", &seats);
        total_train_capacity+=seats;
        list_wagons_append(new_train->wagons, seats);
      }
      new_train->total_capacity = total_train_capacity;
      stations[station_id]->platforms[platform_id]->train = new_train;

      List_Passengers* passengers_queue_premium = stations[station_id]->platforms[platform_id]->passengers_queue_premium;

      while (passengers_queue_premium->head && new_train->total_busy_seats<new_train->total_capacity)
      {
        Passenger* passenger_pop = list_passenger_pop(passengers_queue_premium);
        train_add_passenger(new_train, passenger_pop);
      }
      

    }
    else if (string_equals(command, "PASAJERO"))
    {
      int station_id, platform_id, destination, category;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &destination, &category);
      Platform* platform_selected = stations[station_id]->platforms[platform_id];
      if (!platform_selected->train){
        if (category==0)
        {
          list_passengers_append(platform_selected->passengers_queue_premium,passengers_count,destination,category);
        }
        else
        {
          list_passengers_append(platform_selected->passengers_queue_normal,passengers_count,destination,category);
        };
      }
      else if(platform_selected->train) {
        if(category==0){
          if(platform_selected->train->total_busy_seats < platform_selected->train->total_capacity){
            Passenger* passenger_new = calloc(1,sizeof(Passenger));
            passenger_new -> id = passengers_count;
            passenger_new -> destiny = destination;
            passenger_new -> category = category;
            passenger_new -> next = NULL;
            train_add_passenger(platform_selected->train, passenger_new);
          } else {
            list_passengers_append(platform_selected->passengers_queue_premium,passengers_count,destination,category);
          };
        }
        else if (category==1){

          list_passengers_append(platform_selected->passengers_queue_normal,passengers_count,destination,category);

        }
      }

      passengers_count++;
    }
    else if (string_equals(command, "REMOVER"))
    {
      int station_id, platform_id, car, seat;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &car, &seat);

      Train* train_selected = stations[station_id]->platforms[platform_id]->train;
      Wagon* current = train_selected->wagons->head;
      for (int i = 1; i < car; i++)
      {
        current = current->next;
      }
      if (current->seats[seat]){
        Passenger* passenger_removed = current->seats[seat];
        current->seats[seat] = NULL;
        current->busy_seats -= 1 ;
        train_selected->total_busy_seats -=1;
        fprintf(output_file,"REMOVER %d %d\n",passenger_removed->id,passenger_removed->destiny);
        free(passenger_removed);

        List_Passengers* passengers_queue_premium =stations[station_id]->platforms[platform_id]->passengers_queue_premium;

        while (passengers_queue_premium->head && train_selected->total_busy_seats<train_selected->total_capacity)
        {
          Passenger* passenger_pop = list_passenger_pop(passengers_queue_premium);
          train_add_passenger(train_selected, passenger_pop);
        }

      }
      else{
        printf("No hay una personan en el asiento a remover en el caso REMOVER %d %d %d %d",station_id, platform_id, car, seat);
      }
      





    }
    else if (string_equals(command, "SALIR"))
    {
      int station_id, platform_id;
      fscanf(input_file, "%d %d", &station_id, &platform_id);


    }
    else if (string_equals(command, "LLEGAR"))
    {
      int station_id, platform_id;
      fscanf(input_file, "%d %d", &station_id, &platform_id);


    }
    else if (string_equals(command, "DESAPARECER"))
    {


    }
    else if (string_equals(command, "SEPARAR"))
    {
      int station_id_1, platform_id_1, station_id_2, platform_id_2;
      fscanf(input_file, "%d %d %d %d", &station_id_1, &platform_id_1, &station_id_2, &platform_id_2);


    }
    else if (string_equals(command, "ESTACION"))
    {
      int station_id;
      fscanf(input_file, "%d", &station_id);
      station_print(stations[station_id], output_file);


    }

    /* Leemos la siguiente instrucción */
    fscanf(input_file, "%s", command);
  }
  //imprimir todas las estaciones al final
  all_stations_print(stations, N_STATIONS, output_file);

  /*  [Por implementar] Liberamos nuestras estructuras */
  fclose(input_file);
  fclose(output_file);

  // printf("Estacion %d y Anden %d\n", 1,0);
  //     printf("El Nuevo tren es T%d\n",stations[1]->platforms[0]->train->id);
  //     printf("La cantidad de vagones del tren es: %d\n",stations[1]->platforms[0]->train->n_wagons);
  //     for(Wagon* current = stations[1]->platforms[0]->train->wagons -> head; current; current = current -> next)
  //     {
  //       printf("wagon capacity: %i \n", current -> capacity);
  //       for (int h=0; h<current->capacity; h++){
  //         if (!current->seats[h])
  //         {
  //           printf("Asiento: %s\n", current->seats[h]);
  //         };
          
          
  //       };
  //     }

  // list_passengers_print(list_passengers);
  // stations_print(stations, N_STATIONS);
  
  

  stations_free(stations,N_STATIONS);

  return 0;
}