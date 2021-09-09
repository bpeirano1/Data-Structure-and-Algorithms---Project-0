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

  //Ahora creamos un contador para los pasajeros y trenes: 
  int passengers_count = 0;
  int trains_count = 0;
  List_Passengers* passengers_to_destroy = list_passengers_init();
  Train* train_traveling;



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
        list_wagons_append(new_train->wagons, seats, l);
      }
      new_train->total_capacity = total_train_capacity;
      stations[station_id]->platforms[platform_id]->train = new_train;

      List_Passengers* passengers_queue_premium = stations[station_id]->platforms[platform_id]->passengers_queue_premium;

      while (passengers_queue_premium->head && new_train->total_busy_seats<new_train->total_capacity)
      {
        Passenger* passenger_pop = list_passenger_pop(passengers_queue_premium);
  
        if(new_train->total_busy_seats<new_train->total_capacity){
            train_add_passenger(new_train, passenger_pop);
          list__errase_passengers_append(passengers_to_destroy, passenger_pop);
            }
            else{
              printf("\n");
              printf("Alguien se perdio y se quedo sin subir\n");
              printf("\n");
            }
        
      };
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
            list__errase_passengers_append(passengers_to_destroy, passenger_new);
          } else {
            list_passengers_append(platform_selected->passengers_queue_premium,passengers_count,destination,category);
          };
        }
        else if (category==1){

          list_passengers_append(platform_selected->passengers_queue_normal,passengers_count,destination,category);

        }
      } else{
        printf("Passanger nunca entra al flujo");
      };



      passengers_count++;
    }
    else if (string_equals(command, "REMOVER"))
    {
      int station_id, platform_id, car, seat;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &car, &seat);

      Train* train_selected = stations[station_id]->platforms[platform_id]->train;

      Wagon* current = train_selected->wagons->head;

      for (int i = 1; i <= car; i++)
      {
        current = current->next;
      };

      if (current->seats[seat]->in_seat){
        int passenger_removed_id = current->seats[seat]->id;
        int passenger_removed_destiny = current->seats[seat]->destiny;
        fprintf(output_file,"REMOVER %d %d\n",passenger_removed_id,passenger_removed_destiny);

        current->seats[seat]->in_seat=0;
        current->seats[seat]->id=0;
        current->seats[seat]->destiny=0;
        current->seats[seat]->category=0;
        current->seats[seat]->next = NULL;
        current->busy_seats -= 1 ;
        train_selected->total_busy_seats -= 1;

        List_Passengers* passengers_queue_premium =stations[station_id]->platforms[platform_id]->passengers_queue_premium;

        while (passengers_queue_premium->head && train_selected->total_busy_seats<train_selected->total_capacity)
        {
          Passenger* passenger_pop = list_passenger_pop(passengers_queue_premium);
          if(train_selected->total_busy_seats<train_selected->total_capacity){
            train_add_passenger(train_selected, passenger_pop);
            list__errase_passengers_append(passengers_to_destroy, passenger_pop);
            }
            else{
              printf("\n");
              printf("Alguien se perdio y se quedo sin subir\n");
              printf("\n");
            }
        }

      }
      else{
        printf("No hay una personan en el asiento a remover en el caso REMOVER %d %d %d %d\n",station_id, platform_id, car, seat);
        printf("Debuggeo Train: %i asientos ocupados tren: %i/%i , Vagon: %i asientos ocupados %i/%i,\n", train_selected->id,train_selected->total_busy_seats,train_selected->total_capacity,current->id,current->busy_seats,current->capacity);
        train_print(train_selected);

    }
    }
    else if (string_equals(command, "SALIR"))
    {
      int station_id, platform_id;
      fscanf(input_file, "%d %d", &station_id, &platform_id);
      
      Train* train_selected = stations[station_id]->platforms[platform_id]->train;
      List_Passengers* passengers_queue_normal = stations[station_id]->platforms[platform_id]->passengers_queue_normal;

      while (passengers_queue_normal->head && train_selected->total_busy_seats<train_selected->total_capacity)
        {
          Passenger* passenger_pop = list_passenger_pop(passengers_queue_normal);
          if(train_selected->total_busy_seats<train_selected->total_capacity){
            train_add_passenger(train_selected, passenger_pop);
            list__errase_passengers_append(passengers_to_destroy, passenger_pop);
            }
            else{
              printf("\n");
              printf("Alguien se perdio y se quedo sin subir\n");
              printf("\n");
            }
        }

      train_traveling = train_selected;
      stations[station_id]->platforms[platform_id]->train = NULL;

    }
    else if (string_equals(command, "LLEGAR"))
    {
      int station_id, platform_id;
      fscanf(input_file, "%d %d", &station_id, &platform_id);
      fprintf(output_file,"LLEGAR ");
      train_fprint(train_traveling, output_file);

      for(Wagon* current = train_traveling->wagons-> head; current; current = current -> next)
      {
        for (int i = 0; i < current->capacity; i++)
        {
          if (current->seats[i]->in_seat && current->seats[i]->destiny == station_id)
          {
            current->seats[i]->in_seat=0;
            current->seats[i]->id=0;
            current->seats[i]->destiny=0;
            current->seats[i]->category=0;
            current->seats[i]->next = NULL;
            current->busy_seats -= 1 ;
            train_traveling->total_busy_seats -= 1;
          }   
        }        
        };
        List_Passengers* passengers_queue_premium = stations[station_id]->platforms[platform_id]->passengers_queue_premium;

        while (passengers_queue_premium->head && train_traveling->total_busy_seats<train_traveling->total_capacity)
        {
          Passenger* passenger_pop = list_passenger_pop(passengers_queue_premium);
          train_add_passenger(train_traveling, passenger_pop);
          list__errase_passengers_append(passengers_to_destroy, passenger_pop);
          
        }
        train_traveling->n_station = station_id;
        train_traveling->n_platform = platform_id;

        stations[station_id]->platforms[platform_id]->train=train_traveling;

    }
    else if (string_equals(command, "DESAPARECER"))
    {
      fprintf(output_file,"DESAPARECER ");
      train_fprint(train_traveling, output_file);
      train_traveling = NULL;


    }
    else if (string_equals(command, "SEPARAR"))
    {
      int station_id_1, platform_id_1, station_id_2, platform_id_2;
      fscanf(input_file, "%d %d %d %d", &station_id_1, &platform_id_1, &station_id_2, &platform_id_2);

      // Train* new_train_separated = train_init(trains_count, station_id_2, platform_id_2, length);
      // trains_count++;




    }
    else if (string_equals(command, "ESTACION"))
    {
      int station_id;
      fscanf(input_file, "%d", &station_id);
      station_fprint(stations[station_id], output_file);


    }

    /* Leemos la siguiente instrucción */
    fscanf(input_file, "%s", command);
  }
  //imprimir todas las estaciones al final
  all_stations_fprint(stations, N_STATIONS, output_file);

  /*  [Por implementar] Liberamos nuestras estructuras */
  fclose(input_file);
  fclose(output_file);
  stations_free(stations,N_STATIONS);

  return 0;
}