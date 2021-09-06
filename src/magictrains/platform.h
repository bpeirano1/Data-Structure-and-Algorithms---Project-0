#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "passenger.h"
#include "train.h"

#pragma once

struct platform;

typedef struct platform Platform;

struct platform {
    int id;
    List_Passengers* passengers_queue;
    Train* train;
};

//Init de platformd
Platform** platforms_init(int NPlatform);

// Para imprimir el array
void platforms_print(Platform** self, int NPlatform);

void platforms_free(Platform** self, int NPlatform);