#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform** platforms_init(int NPlatform)
{
    Platform** platforms = calloc(NPlatform, sizeof(Platform*));

    for (int id=0; id<NPlatform; id++){

    Platform* platform = calloc(1,sizeof(Platform));

    *platform = (Platform) 
    {
        .id = id,
    };

    platforms[id]=platform;

    };

    return platforms;
    
};

void platforms_print(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        printf("Anden %d\n",self[id]->id);
    };
};

void platforms_free(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        free(self[id]);
    };
    free(self);
};