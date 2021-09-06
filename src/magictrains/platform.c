#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform** platforms_init(int NPlatform)
{
    Platform** platforms = calloc(NPlatform, sizeof(Platform*));

    for (int id=0; id<NPlatform; id++){

    Platform* platform = calloc(1,sizeof(Platform));
    List_Passengers* passengers_queue_normal = list_passengers_init();
    List_Passengers* passengers_queue_premium = list_passengers_init();

    *platform = (Platform) 
    {
        .id = id,
        .passengers_queue_normal = passengers_queue_normal,
        .passengers_queue_premium = passengers_queue_premium,
        .train = NULL
    };

    platforms[id]=platform;

    };

    return platforms;
    
};

void platforms_print(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        printf("A%d",self[id]->id);
        passengers_queue_print(self[id]->passengers_queue_premium);
        passengers_queue_print(self[id]->passengers_queue_normal);
        printf("\n");
        if (self[id]->train)
        {
            train_print(self[id]->train);
        }; 
    };
};
void passengers_queue_print(List_Passengers* list){
    for(Passenger* current = list -> head; current; current = current -> next)
  {
    printf(" %d-%d-%d", current -> id, current->destiny, current->category);
  };
  

};

void platforms_free(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        free(self[id]);
    };
    free(self);
};