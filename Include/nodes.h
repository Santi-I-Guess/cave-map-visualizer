
#ifndef NODES_H
#define NODES_H

#include "raylib.h"
#include "sqlite3.h"

typedef struct {
        int x;
        int y;
        int z;
        char label[80]; 
        Color color;
} Node;

typedef struct {
        Node *first;
        Node *second;
        Color color;
} Connection;

void create_tables(sqlite3 *db);
sqlite3 *database_open(int argc, char **argv);

#endif
