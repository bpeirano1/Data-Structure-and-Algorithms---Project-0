#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wagon.h"


#pragma once

struct train;

typedef struct train Train;

struct train {
    int id;
    int n_station;
    int n_platform;
    int n_wagons;
    List_Wagons* wagons;
    int total_capacity;
    int total_busy_seats;

};

//Init de station
Train* train_init(int id, int n_station, int n_platform, int n_wagons);

// Para imprimir el array
void train_print(Train* self);

// Para liberar memoria
void train_free(Train* self);
