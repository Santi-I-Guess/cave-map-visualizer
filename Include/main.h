
#ifndef MAIN_H
#define MAIN_H

extern const int width;
extern const int height;
FILE *get_data_file(int argc, char *argv[]);
void draw_stats(Camera *camera, Font *le_font);

#endif
