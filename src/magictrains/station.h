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
void all_stations_fprint(Station** self, int NStation, FILE* output_file);

void station_fprint(Station* self, FILE* output_file);

// Para liberar memoria
void stations_free(Station** self, int NStation);