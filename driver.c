#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "driver.h"
#include "array.h"
#include "hash_AVL.h"
#include <unistd.h>

int test_init(int type, int trials, unsigned int n) {
    srand(time(NULL));

    unsigned long start = 0;
    unsigned long end = 0;
    unsigned long sum = 0;

    unsigned int *value_array = number_generator(n);
    if (value_array == NULL) {
        return -1;
    }
    if (type == 0) {
        printf("array test starting: \n");
        void *data_structure = array_create(value_array, value_array, n);
        printf("create finished\n");

        for (int i = 0; i < trials; i++) {
            start = clock();
            unsigned int temp_key = (rand() * rand()) % n;
            
            unsigned int search_result = array_search(data_structure, temp_key, n);
            if (search_result == temp_key) {
                end = clock();
                sum += (end - start);
                printf("search #%d    key: %d        proportion: %f       successful, time: %f\n", i, temp_key, (double) ((temp_key * 1.0) / n), (double) (end - start) / CLOCKS_PER_SEC);
            }
            else {
                printf("search #%d failed\n", i);
                value_array_destroy((void *) value_array);
                return -1;
            }
        }
    }
    
    else if (type == 1) {
        printf("hash_AVL test starting: \n");
        void *data_structure = hash_AVL_create(value_array, value_array, n);
        printf("create finished\n");

        for (int i = 0; i < trials; i++) {
            start = clock();
            unsigned long temp_key = (rand() * rand()) % n;
            
            unsigned long search_result = hash_AVL_search(data_structure, temp_key);
            if (search_result == temp_key) {
                unsigned long end = clock();
                sum += (end - start);
                printf("search #%d    key: %ld        proportion: %f       successful, time: %f\n", i, temp_key, (double) ((temp_key * 1.0) / n), (double) (end - start) / CLOCKS_PER_SEC);
            }
            else {
                printf("search #%d failed\n", i);
                value_array_destroy((void *) value_array);
                return -1;
            }
        }
    }
    value_array_destroy((void *) value_array);
    return (int) sum;
}


// char **keys_generator(int n) {
//     printf("key generator start\n");
//     char **result = malloc(sizeof(char *) * n);
//     if (result == NULL) {
//         printf("key_generator error\n");
//         return NULL;
//     }
//     int digits = log10(n) + 1;
//     for (int i = 0; i < n; i++) {
//         char *key = malloc(sizeof(char) * (3 + digits + 1)); // key123456\0
//         if (key == NULL) {
//             printf("key_generator error2\n");
//             for (int j = 0; j < i; j++) {
//                 free(result[j]);
//             }
//             free(result);

//             return NULL;
//         }
//         sprintf(key, "key%d", i);
//         result[i] = key;
//     }
//     return result;
// }

unsigned int *number_generator(unsigned int n) {
    // printf("number generator start\n");
    unsigned int *result = malloc(sizeof(unsigned int) * n);
    if (result == NULL) {
        printf("number generator error\n");
        return NULL;
    }
    for (unsigned int i = 0; i < n; i++) {
        result[i] = i;
    }
    return result;
}

// void key_array_destroy(char** input, int n) {
//     for (int i = 0; i < n; i++) {
//         free(input[i]);
//     }
//     free(input);
// }
void value_array_destroy(unsigned long *input) {
    free(input);
}

// char *test_return(char **array, int index) {
//     // printf("this is test return result: %s \n", array[index]);
//     return array[index];
// }

// int test_string_input(char *input) {
//     if (input == NULL) {
//         return 0;
//     }
//     else {
        
//         printf("this is test return result: %s \n", input);
//         return 1;
//     }
// }