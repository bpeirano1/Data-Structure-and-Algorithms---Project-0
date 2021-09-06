#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform** platforms_init(int NPlatform)
{
    Platform** platforms = calloc(NPlatform, sizeof(Platform*));

    for (int id=0; id<NPlatform; id++){

    Platform* platform = calloc(1,sizeof(Platform));
    List_Passengers* passengers_queue = list_passengers_init();

    *platform = (Platform) 
    {
        .id = id,
        .passengers_queue = passengers_queue,
        .train = NULL
    };

    platforms[id]=platform;

    };

    return platforms;
    
};

void platforms_print(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        printf("-Anden %d\n",self[id]->id);
        train_print(self[id]->train);
    };
};

void platforms_free(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        free(self[id]);
    };
    free(self);
};