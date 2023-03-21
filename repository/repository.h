#pragma once

#include "../domain/country.h"

typedef struct {
    Country** data;
    int size;
} Repository;

Repository* repository_create();

void repository_destroy(Repository* repository);

Country** repository_get_all(Repository* repository);

int repository_get_size(Repository* repository);

int repository_find_country(Repository* repository, Country* country_to_find);

int repository_add_country(Repository* repository, Country* new_country);

int repository_remove_country(Repository* repository, Country* country_to_remove);

int repository_remove_country_by_name(Repository* repository, char* name);