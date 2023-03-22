#include "undo_redo.h"
#include <stdlib.h>

Undo* undo_create() {
    Undo* new_undo = malloc(sizeof(Undo));
    if (!new_undo)
        return NULL;
    new_undo->undo_capacity = 5;
    new_undo->undo_size = 0;
    new_undo->undo_list = (Repository**) malloc(sizeof(Repository*) * new_undo->undo_capacity);
    if (!new_undo->undo_list) {
        free(new_undo);
        return NULL;
    }
    return new_undo;
}

void undo_destroy(Undo* undo) {
    for (int i = 0; i < undo->undo_size; ++i)
        repository_destroy(undo->undo_list[i]);
    free(undo->undo_list);
    free(undo);
}

void undo_resize(Undo* undo, int resize_factor) {
    undo->undo_capacity *= resize_factor;
    undo->undo_list = (Repository**) realloc(undo->undo_list, undo->undo_capacity * sizeof(Repository*));
    if (undo->undo_list == NULL) {
        undo->undo_capacity = 0;
        undo->undo_size = 0;
    }
}

void undo_add(Undo* undo, Repository* repository) {
    if (undo->undo_size >= undo->undo_capacity)
        undo_resize(undo, 2);
    Repository* copy;
    repository_make_copy(&copy, repository);
    undo->undo_list[undo->undo_size] = copy;
    undo->undo_size++;
}

int undo(Undo* undo, Repository** repository, Redo* redo) {
    if (undo->undo_size == 0)
        return 0;
    redo_add(redo, *repository);
    Repository* restore_repo;
    Repository* old_repo = *repository;
    repository_make_copy(&restore_repo, undo->undo_list[undo->undo_size - 1]);
    *repository = restore_repo;
    repository_destroy(old_repo);
    repository_destroy(undo->undo_list[undo->undo_size - 1]);
    undo->undo_size--;
    return 1;
}

Redo* redo_create() {
    Redo* new_redo = malloc(sizeof(Redo));
    if (!new_redo)
        return NULL;
    new_redo->redo_capacity = 5;
    new_redo->redo_size = 0;
    new_redo->redo_list = (Repository**) malloc(sizeof(Repository*) * new_redo->redo_capacity);
    if (!new_redo->redo_list) {
        free(new_redo);
        return NULL;
    }
    return new_redo;
}


void redo_destroy(Redo* redo) {
    for (int i = 0; i < redo->redo_size; ++i)
        repository_destroy(redo->redo_list[i]);
    free(redo->redo_list);
    free(redo);
}


void redo_resize(Redo* redo, int resize_factor) {
    redo->redo_capacity *= resize_factor;
    redo->redo_list = (Repository**) realloc(redo->redo_list, redo->redo_capacity * sizeof(Repository*));
    if (redo->redo_list == NULL) {
        redo->redo_capacity = 0;
        redo->redo_size = 0;
    }
}


void redo_add(Redo* redo, Repository* repository) {
    if (redo->redo_size >= redo->redo_capacity)
        redo_resize(redo, 2);
    Repository* copy;
    repository_make_copy(&copy, repository);
    redo->redo_list[redo->redo_size] = copy;
    redo->redo_size++;
}


int redo(Redo* redo, Repository** repository, Undo* undo) {
    if (redo->redo_size == 0)
        return 0;
    undo_add(undo, *repository);
    Repository* restore_repo;
    Repository* old_repo = *repository;
    repository_make_copy(&restore_repo, redo->redo_list[redo->redo_size - 1]);
    *repository = restore_repo;
    repository_destroy(old_repo);
    repository_destroy(redo->redo_list[redo->redo_size - 1]);
    redo->redo_size--;
    return 1;
}

