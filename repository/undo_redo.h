#pragma once

#include "repository.h"


typedef struct {
    Repository** undo_list;
    int undo_size;
    int undo_capacity;
} Undo;

typedef struct {
    Repository** redo_list;
    int redo_size;
    int redo_capacity;
} Redo;

Undo* undo_create();

void undo_destroy(Undo*);

void undo_resize(Undo*, int resize_factor);

void undo_add(Undo*, Repository*);

int undo(Undo*, Repository**, Redo*);


Redo* redo_create();

void redo_destroy(Redo*);

void redo_resize(Redo*, int resize_factor);

void redo_add(Redo*, Repository*);

int redo(Redo*, Repository**, Undo*);

