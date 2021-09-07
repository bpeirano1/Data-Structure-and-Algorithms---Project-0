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
        .wagons = list_wagons,
        .total_capacity = 0,
        .total_busy_seats = 0
    };

    return train;
};

void train_print(Train* self, FILE* output_file){
    fprintf(output_file,"T%d |",self->id);
    list_wagons_print(self->wagons, output_file);
    fprintf(output_file,"\n");
};

// Para liberar memoria
void train_free(Train* self){
    free(self);
};