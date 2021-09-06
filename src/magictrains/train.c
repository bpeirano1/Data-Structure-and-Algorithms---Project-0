#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

Train* train_init(int id, int n_station, int n_platform, int n_wagons){
    Train* train = calloc(1, sizeof(Train));
    List_Wagons* list_wagons = list_wagons_init();
    
    *train = (Train){
        .id = id,
        .n_station = n_station,
        .n_platform = n_platform,
        .n_wagons = n_wagons,
        .wagons = list_wagons
    };

    return train;
};

void train_print(Train* self){
    printf("--T%d | Cantidad de vagones: %d | ",self->id, self -> n_wagons);
    list_wagons_print(self->wagons);
    printf("\n");
};

// Para liberar memoria
void train_free(Train* self){
    free(self);
};