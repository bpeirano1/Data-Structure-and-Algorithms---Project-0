#include "station.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station** stations_init(int NStation)
{
    Station** stations = calloc(NStation, sizeof(Station*));

    for (int id=0; id<NStation; id++){

    Station* station = calloc(1,sizeof(Station));

    *station = (Station) 
    {
        .id = id,
        .n_platform = 0,
        .platforms = NULL
    };

    stations[id]=station;

    };

    return stations;
    
};

void all_stations_print(Station** self, int NStation){
    for (int id=0; id<NStation; id++){
        station_print(self[id]);
        };
    };
    
void station_print(Station* self){
    printf("ESTACION %d\n", self->id);
    platforms_print(self->platforms,self->n_platform);

};

void stations_free(Station** self, int NStation){
    for (int id=0; id<NStation; id++){
        platforms_free(self[id]->platforms,self[id]->n_platform);
        free(self[id]);
    };
    free(self);
};
