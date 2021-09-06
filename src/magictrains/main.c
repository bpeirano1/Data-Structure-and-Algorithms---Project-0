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
  List_Passengers* list_passengers = list_passengers_init();

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

      for (int l = 0; l < length; l++)
      {
        fscanf(input_file, "%d", &seats);
        list_wagons_append(new_train->wagons, seats);
      }
      stations[station_id]->platforms[platform_id]->train = new_train;
      // printf("Estacion %d y Anden %d\n", station_id,platform_id);
      // printf("El Nuevo tren es T%d\n",stations[station_id]->platforms[platform_id]->train->id);
      // printf("La cantidad de vagones del tren es: %d\n",stations[station_id]->platforms[platform_id]->train->n_wagons);
      // for(Wagon* current = stations[station_id]->platforms[platform_id]->train->wagons -> head; current; current = current -> next)
      // {
      //   printf("wagon capacity: %i \n", current -> capacity);
      // }


    }
    else if (string_equals(command, "PASAJERO"))
    {
      int station_id, platform_id, destination, category;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &destination, &category);
      list_passengers_append(list_passengers, passengers_count,destination,category);
      passengers_count++;
    }
    else if (string_equals(command, "REMOVER"))
    {
      int station_id, platform_id, car, seat;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &car, &seat);


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


    }

    /* Leemos la siguiente instrucción */
    fscanf(input_file, "%s", command);
  }

  /*  [Por implementar] Liberamos nuestras estructuras */
  fclose(input_file);
  fclose(output_file);

  printf("Estacion %d y Anden %d\n", 1,0);
      printf("El Nuevo tren es T%d\n",stations[1]->platforms[0]->train->id);
      printf("La cantidad de vagones del tren es: %d\n",stations[1]->platforms[0]->train->n_wagons);
      for(Wagon* current = stations[1]->platforms[0]->train->wagons -> head; current; current = current -> next)
      {
        printf("wagon capacity: %i \n", current -> capacity);
      }

  // list_passengers_print(list_passengers);
  // stations_print(stations, N_STATIONS);

  stations_free(stations,N_STATIONS);

  return 0;
}