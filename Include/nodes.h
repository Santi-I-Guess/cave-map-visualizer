
#ifndef NODES_H
#define NODES_H

#include "raylib.h"

typedef struct {
        int x;
        int y;
        int z;
        char label[80]; 
        Color color;
} Node;

void draw_checkpoints(FILE *data_file);


#endif
