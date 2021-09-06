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

void stations_print(Station** self, int NStation){
    for (int id=0; id<NStation; id++){
        printf("Estacion %d\n",self[id]->id);
        for (int j=0; j<self[id]->n_platform;j++){
            platforms_print(self[id]->platforms, self[id]->n_platform);
        };
    };
};
void stations_free(Station** self, int NStation){
    for (int id=0; id<NStation; id++){
        platforms_free(self[id]->platforms,self[id]->n_platform);
        free(self[id]);
    };
    free(self);
};