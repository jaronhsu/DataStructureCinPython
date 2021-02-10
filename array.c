#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct node {
//     int key;
//     int value;
// };

// struct node *global_structure;

void *array_create(unsigned int *keys, unsigned int *values, unsigned int n) {
    unsigned int *result = keys;

    return result;
}

unsigned int array_search(void *data_structure, unsigned int key, unsigned int n) {
    // printf("array search start, searching for %ld       %f\n", key, (double) ((key * 1.0) / n));
    // printf("array search n: %d\n", n);
    // printf("array search key: %s\n", key);
    // struct node *global_structure = (struct node*)data_structure;
    unsigned int *global_structure = (unsigned int *) data_structure;
    // printf("array search running\n");
    for (unsigned int i = 0; i < n; i++) {
        if (key == global_structure[i]) {
            return global_structure[i];
        }
    }
    return -1;
}

void array_destroy(void *data_structure) {
    // printf("array destroy start\n");
    struct node *global_structure = (struct node*)data_structure;
    free(global_structure);
}