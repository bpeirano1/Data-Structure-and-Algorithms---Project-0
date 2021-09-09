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

void all_stations_fprint(Station** self, int NStation, FILE* output_file){
    for (int id=0; id<NStation; id++){
        station_fprint(self[id], output_file);
        };
    };

void station_fprint(Station* self, FILE* output_file){
    fprintf(output_file,"ESTACION %d\n", self->id);
    platforms_fprint(self->platforms,self->n_platform, output_file);

};

void stations_free(Station** self, int NStation){
    for (int id=0; id<NStation; id++){
        platforms_free(self[id]->platforms,self[id]->n_platform);
        free(self[id]);
    };
    free(self);
};
