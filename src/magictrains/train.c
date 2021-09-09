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

void train_fprint(Train* self, FILE* output_file){
    fprintf(output_file,"T%d |",self->id);
    list_wagons_fprint(self->wagons, output_file);
    fprintf(output_file,"\n");
};
void train_print(Train* self){
    printf("T%d |",self->id);
    list_wagons_print(self->wagons);
    printf("\n");
};

// Para liberar memoria
void train_free(Train* self){
    free(self);
};

void train_add_passenger(Train* train, Passenger* passenger){
    if (train->total_busy_seats < train->total_capacity){
        int asiento_encontrado=0;
        int wagon_count = 0;

        Wagon* current = train->wagons->head;
        while (!asiento_encontrado && wagon_count < train->n_wagons)
        {
            if(current->busy_seats < current->capacity){
                wagon_add_person(current,passenger,train->id);
                asiento_encontrado = 1;
                train->total_busy_seats += 1;
            };
            current = current->next;
            wagon_count++;

        };
        if(!asiento_encontrado){
            
            printf("Error no se encontro asiento, cuando deberían haber disponible");
        };
    };
    
};