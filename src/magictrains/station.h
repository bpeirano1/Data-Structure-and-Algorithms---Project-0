#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "platform.h"

#pragma once

struct station;

typedef struct station Station;

struct station {
    int id;
    int n_platform;
    Platform** platforms;

};

//Init de station
Station** stations_init(int NStation);

// Para imprimir el array
void all_stations_print(Station** self, int NStation);

void station_print(Station* self);

// Para liberar memoria
void stations_free(Station** self, int NStation);