#pragma once

typedef struct {
    void** data;
    int element_size;
    int capacity;
    int size;
} Vector;

Vector* vector_create(int element_size);

void vector_destroy(Vector*, void destroy_item());

void vector_resize(Vector*, int resize_factor);

void* vector_get_item(Vector*, int index);

void vector_add_item(Vector*, void* new_item);

int vector_get_size(Vector*);

void** vector_get_all(Vector*);

int vector_remove_item(Vector* vector, int item_index, void (*destroy_item)());