#include <stdio.h>
#include <stdlib.h>

#include "../Include/utils.h"

int init_array(Array *alpha) {
        alpha->items = (Node**)malloc(16 * sizeof(Node*));
        if (!alpha->items) {
                fprintf(stderr, "array initialization failed\n");
                return 1;
        }
        alpha->count = 0;
        alpha->capacity = 16;
        return 0;
}

int deinit_array(Array *alpha) {
        if (!alpha->items)
                return 1;

        for (size_t i = 0; i < alpha->count; ++i)
                if ((Node *)alpha->items[i])
                        free(alpha->items[i]);
        free(alpha->items);

        return 0;
}

int expand_array(Array *alpha) {
        int new_cap = alpha->capacity * 2;
        Node **p_temp = (Node**)realloc(alpha->items, new_cap);
        if (!p_temp) {
                fprintf(stderr, "array reallocation failed\n");
                return 1;
        }

        alpha->items = p_temp;
        alpha->capacity *= 2;
        return 0;
}

int append_array(Array *alpha, Node *beta) {
        if (alpha->count + 1 == alpha->capacity) {
                int result = expand_array(alpha);
                if (result) {
                        return 1;
                }
        }

        alpha->items[alpha->count] = beta;
        alpha->count += 1;
}

Node *get_array(Array *alpha, size_t idx) {
        if (idx >= alpha->count) {
                fprintf(stderr, "out of range array get\n");
                return NULL;
        }

        return alpha->items[idx];
}
