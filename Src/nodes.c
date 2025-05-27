#include <stdio.h> // FILE*
#include <string.h>

#include "raylib.h"
#include "../Include/nodes.h"

// should i load the points on the heap?

void draw_checkpoints(FILE *data_file) {
        fseek(data_file, 0, SEEK_SET);
        while (!feof(data_file)) {
                char buffer[80];
                fgets(buffer, sizeof(buffer), data_file);
                int curr_x, curr_y, curr_z;
                int next_x, next_y, next_z;
                if (buffer[0] == 'P') {
                        sscanf(buffer, "P %d %d %d", &curr_x, &curr_y, &curr_z);
                        DrawSphere((Vector3){curr_x, curr_y, curr_z}, 0.5, RED);
                } else if (buffer[0] == 'C') {
                        sscanf(buffer, "C %d %d %d %d %d %d",
                               &curr_x, &curr_y, &curr_z, &next_x, &next_y, &next_z);
                        DrawCylinderEx(
                                (Vector3){curr_x, curr_y, curr_z},
                                (Vector3){next_x, next_y, next_z},
                                0.3, 0.3, 3, ORANGE
                        );
                }
                // printf("\e[35mdrew %d %d %d\n\e[0m", curr_x, curr_y, curr_z);
        }
}
