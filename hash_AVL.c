#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "hash_AVL.h"

typedef struct _node {
  unsigned int key;
  unsigned int value; 
  struct _node *left;
  struct _node *right;
  struct _node *parent;
  size_t height;
} node;

struct gmap {
  size_t capacity;
  size_t size;
  node **table;
};

#define GMAP_INITIAL_CAPACITY 2

// size_t gmap_compute_index(const void *key, size_t (*hash)(const void *), size_t size);
// void gmap_embiggen(gmap *m, size_t n);
// void gmap_table_add(node **table, node *n, size_t capacity);
void gmap_table_add(node **table, node *n, size_t capacity);
// node *gmap_table_find_key(node **table, const void *key, size_t capacity);

int compare(unsigned int a, unsigned int b) {
  if (a < b) {
    return -1;
  }
  else if (a == b) {
    return 0;
  }
  else {
    return 1;
  }
}

size_t hash29(unsigned int key) {
  char key_holder[11];
  char *s = key_holder;
  sprintf(key_holder, "%i", key);

  size_t sum = 0;
  size_t factor = 29;
  while (s != NULL && *s != '\0') {
    sum += *s * factor;
    s++;
    factor *= 29;
  }

  return sum;
}

void *hash_AVL_create(unsigned int *keys, unsigned int *values, unsigned int n) {
  gmap *result = malloc(sizeof(gmap));
  if (result == NULL) {
    return NULL;
  }
  result->size = 0;
  result->table = malloc(sizeof(node *) * GMAP_INITIAL_CAPACITY);
  result->capacity = (result->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
  for (size_t i = 0; i < result->capacity; i++) {
    result->table[i] = NULL;
  }
  for (unsigned int i = 0; i < n; i++) {
    // printf("for loop running\n");
    if (!gmap_put(result, keys[i], values[i])) {
      printf("hash_avl create error\n");
      // printf("asdfasdfasdf\n");
      return NULL;
    }
  }
  return result;
}

node *gmap_table_find_key(node **table, unsigned int key, size_t capacity) {
  size_t i = gmap_compute_index(key, capacity); // compute starting location for search from hash function
  node *curr = table[i];
  int direction = 0;
  while (1) {
    if (curr == NULL) { //ends loop when get to end or when equal
      break;
    }
    direction = compare(key, curr->key); //if what we r looking for is smaller, go left
    if (direction == 0) {
      break;
    }
    else if (direction < 0) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  return curr;
}

bool gmap_put(gmap *m, unsigned int key, unsigned int value) {
  // printf("put start\n");
  if (m == NULL) {
    return false;
  }
  node *n = gmap_table_find_key(m->table, key, m->capacity);
  if (n != NULL) { // key already present
    n->value = value;
    return false;
  }
  if (m->size >= m->capacity) { // new key, value pair -- check capacity
    gmap_embiggen(m, m->capacity * 2); // grow
  }
  n = malloc(sizeof(node)); // add to table
  if (n != NULL) {
    // printf("putting\n");
    n->key = key;
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    n->parent = NULL; //to be decided in add
    gmap_table_add(m->table, n, m->capacity);
    m->size++;
    return true;
  }
  else {
    return false;
  }
}

size_t find_h(node *curr) {
  if (curr == NULL) {
    return 0;
  }
  if (curr->left == NULL && curr->right == NULL){
    return 1;
  }
  else if (curr->left == NULL) {
    return curr->right->height + 1;
  }
  else if (curr->right == NULL) {
    return curr->left->height + 1;
  }
  else if (curr->left->height < curr->right->height){
    return curr->right->height + 1;
  }
  else {
    return curr->left->height + 1;
  }
}

int balance(node *curr) {
  return find_h(curr->right) - find_h(curr->left);
}

node *left_rot(node *curr) {
  curr->right->parent = curr->parent;
  node *temp = curr->right->left;
  curr->right->left = curr;
  curr->parent = curr->right;
  curr = curr->right;
  curr->left->right = temp;
  
  if (temp != NULL) {
    temp->parent = curr->left;
  }
  curr->left->height = find_h(curr->left);
  curr->height = find_h(curr);

  node *updater = curr->parent;
  while (updater != NULL) {
    updater->height = find_h(updater);
    updater = updater->parent;
  }

  return curr;
}

node *right_rot(node *curr) {
  curr->left->parent = curr->parent; //connect left child with grandparent
  node *temp = curr->left->right; //save left->right
  curr->left->right = curr; //right child of child is now parent
  curr->parent = curr->left; //left child is now parent of parent
  curr = curr->left; //curr is now left child
  curr->right->left = temp; // temp; //previous parent's left is now NULL
  if (temp != NULL) {
    temp->parent = curr->right;
  }
  curr->right->height = find_h(curr->right);
  curr->height = find_h(curr);
  
  node *updater = curr->parent;
  while (updater != NULL) {
    updater->height = find_h(updater);
    updater = updater->parent;
  }

  return curr;
}

void gmap_table_add(node **table, node *n, size_t capacity) {
  size_t i = gmap_compute_index(n->key, capacity);
  node **curr = &table[i];
  node *parent_tracker = NULL; //the first node inserted will have a null parent
  while (*curr != NULL) {
    int direction = compare(n->key, (*curr)->key);
    if (direction < 0) {
      parent_tracker = *curr;
      curr = &(*curr)->left;
    }
    else {
      parent_tracker = *curr;
      curr = &(*curr)->right;
    }
  }
  n->parent = parent_tracker;
  *curr = n;
  node *b = *curr;
  while (b != NULL) {// && balance(b) != 0) {
    node **child; //pointer from previous parent to child, to be filled with new top of subtree
    if (b->parent == NULL) { //this means curr is the top node
      child = &table[i];
    }
    else if (b->parent->left == b) { //b is the left child of its parent
      child = &b->parent->left;
    }
    else if (b->parent->right == b) { //b is right child of parent
      child = &b->parent->right;
    }
    b->height = find_h(b);
    if (balance(b) < -1) { //rotate right
      if (balance(b->left) > 0){ //trigger left
        node **child_special = &b->left;
        *child_special = left_rot(b->left);
      }
      *child = right_rot(b);
    }
    else if (balance(b) > 1) { //rotate left
      if (balance(b->right) < 0){
        node **child_special = &b->right;
        *child_special = right_rot(b->right);
      }
      *child = left_rot(b);
    }
    else { //don't iterate after a rot, let it happen as it loops
      b = b->parent;
    }
  }
}

void embiggen_helper(node **bigger_table, node *n, size_t new_cap) {
  if (n != NULL) {
    embiggen_helper(bigger_table, n->left, new_cap);
    embiggen_helper(bigger_table, n->right, new_cap);
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->height = 1;
    gmap_table_add(bigger_table, n, new_cap);
  }
}

void gmap_embiggen(gmap *m, size_t n) {
  size_t bigger_capacity = n;
  node **bigger = calloc(bigger_capacity, sizeof(node *));
  if (bigger != NULL) {
    for (int i = 0; i < m->capacity; i++) {
      embiggen_helper(bigger, m->table[i], bigger_capacity);
    }
    free(m->table);
    m->table = bigger;
    m->capacity = bigger_capacity;
  }
}

size_t gmap_compute_index(unsigned int key, size_t size) {
  return (hash29(key) % size + size) % size;
}

bool gmap_contains_key(const gmap *m, unsigned int key) {
  if (m == NULL) {
    return false;
  }
  return gmap_table_find_key(m->table, key, m->capacity) != NULL;
}

unsigned int hash_AVL_search(gmap *m, unsigned int key) {
  if (m == NULL) {
    return 0;
  }
  
  node *n = gmap_table_find_key(m->table, key, m->capacity);
  if (n == NULL) {
    return 0;
  }
  else {
    return n->value;
  }
}

// void for_each_helper(node *n, void (*f)(const void *, void *, void *), void *arg) {
//   if (n != NULL) {
//     for_each_helper(n->left, f, arg);
//     for_each_helper(n->right, f, arg);
//     f(n->key, n->value, arg);
//   }
// }

// void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg) {
//   if (m == NULL || f == NULL) {
//     return;
//   }
//   for (int i = 0; i < m->capacity; i++) {
//     for_each_helper(m->table[i], f, arg);
//   }
// }

void destroy_helper(node *n) {
  if (n != NULL) {
    destroy_helper(n->left);
    destroy_helper(n->right);
    // free(n->key);
    free(n);
  }
}

void gmap_destroy(gmap *m) {
  if (m == NULL) {
    return;
  }
  for (size_t i = 0; i < m->capacity; i++) {
    destroy_helper(m->table[i]);
  }
  free(m->table);
  free(m);
}