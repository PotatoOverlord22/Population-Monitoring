#include "vector.h"
#include <stdlib.h>

Vector* vector_create(int element_size) {
    Vector* new_vector = malloc(sizeof(Vector));
    if (new_vector == NULL)
        return NULL;
    new_vector->capacity = 5;
    new_vector->size = 0;
    new_vector->element_size = element_size;
    new_vector->data = (void**) malloc(new_vector->capacity * new_vector->element_size);
    if (new_vector->data == NULL) {
        free(new_vector);
        return NULL;
    }
    return new_vector;
}

void vector_destroy(Vector* vector, void destroy_item()) {
    for (int i = 0; i < vector->size; ++i)
        destroy_item(vector->data[i]);
    free(vector->data);
    free(vector);
}

void vector_resize(Vector* vector, int resize_factor) {
    vector->capacity *= resize_factor;
    vector->data = (void**) realloc(vector->data, vector->capacity * vector->element_size);
    if (vector->data == NULL) {
        vector->size = 0;
        vector->capacity = 0;
    }
}

void* vector_get_item(Vector* vector, int index) {
    if (index >= vector->size)
        return NULL;
    return vector->data[index];
}

void vector_add_item(Vector* vector, void* new_item) {
    if (vector->size >= vector->capacity) {
        vector_resize(vector, 2);
    }
    vector->data[vector->size] = new_item;
    vector->size++;
}

int vector_get_size(Vector* vector) {
    return vector->size;
}

void** vector_get_all(Vector* vector) {
    return vector->data;
}

int vector_remove_item(Vector* vector, int item_index, void (*destroy_item)()){
    if (item_index >= vector->size)
        return 0;
    void* item_to_free = vector->data[item_index];
    for (int i = item_index; i < vector->size - 1; ++i){
        vector->data[i] = vector->data[i + 1];
    }
    destroy_item(item_to_free);
    vector->size--;
    return 1;
}