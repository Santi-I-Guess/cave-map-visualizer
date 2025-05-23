#include <stdio.h> // FILE*
#include <string.h>

#include "raylib.h"
#include "../Include/checkpoints.h"

void draw_checkpoints(FILE *data_file) {
        fseek(data_file, 0, SEEK_SET);
        while (!feof(data_file)) {
                char buffer[80];
                int curr_x, curr_y, curr_z;
                fgets(buffer, sizeof(buffer), data_file);
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strcmp(buffer, "") == 0)
                        break;
                sscanf(buffer, "%d %d %d\n", &curr_x, &curr_y, &curr_z);
                DrawSphere((Vector3){curr_x, curr_y, curr_z}, 0.2, RED);
                // printf("\e[35mdrew %d %d %d\n\e[0m", curr_x, curr_y, curr_z);
        }
}
