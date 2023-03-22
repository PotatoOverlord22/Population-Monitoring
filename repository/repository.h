#pragma once

#include "../domain/country.h"
#include "vector.h"

typedef struct {
    Vector* data;
} Repository;

Repository* repository_create();

void repository_destroy(Repository* repository);

void** repository_get_all(Repository* repository);

int repository_get_size(Repository* repository);

int repository_find_country(Repository* repository, Country* country_to_find);

int repository_add_country(Repository* repository, Country* new_country);

int repository_remove_country(Repository* repository, Country* country_to_remove);

int repository_remove_country_by_name(Repository* repository, char* name);

void repository_make_copy(Repository** destination_repository, Repository* source_repository);