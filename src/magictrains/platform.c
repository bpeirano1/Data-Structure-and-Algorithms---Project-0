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

void platforms_fprint(Platform** self, int NPlatform, FILE* output_file){
    for (int id=0; id<NPlatform; id++){
        fprintf(output_file,"A%d",self[id]->id);
        passengers_queue_fprint(self[id]->passengers_queue_premium, output_file);
        passengers_queue_fprint(self[id]->passengers_queue_normal, output_file);
        fprintf(output_file,"\n");
        if (self[id]->train)
        {
            train_fprint(self[id]->train,output_file);
        }; 
    };
};
void passengers_queue_fprint(List_Passengers* list, FILE* output_file){
    for(Passenger* current = list -> head; current; current = current -> next)
  {
    fprintf(output_file," %d-%d-%d", current -> id, current->destiny, current->category);
  };
  

};

void platforms_free(Platform** self, int NPlatform){
    for (int id=0; id<NPlatform; id++){
        free(self[id]);
    };
    free(self);
};