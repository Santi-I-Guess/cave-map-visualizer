
#ifndef UTILS_H
#define UTILS_H

#include "nodes.h"

typedef struct {
        size_t count;
        size_t capacity;
        Node **items; // nodes or connections
} Array;

// all return 0 if no memory error occured, else return 1
// though, this means i am juggling several possible failures between functions
// better than nothing, though

int init_array(Array *alpha);
int deinit_array(Array *alpha);
int expand_array(Array *alpha);
int append_array(Array *alpha, Node *beta);
Node *get_array(Array *alpha, size_t idx);

#endif
