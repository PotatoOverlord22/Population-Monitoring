#pragma once

#include "../domain/country.h"

typedef struct {
    Country* data;
    int size;
} Repository;

Repository* create_repository();

void destroy_repository(Repository*);

Country* get_all(Repository*);

int get_size(Repository*);

int find_country(Repository*, Country*);

int add_country(Repository*, Country* new_country);

int remove_country(Repository*, Country* country_to_remove);

int remove_country_by_name(Repository*, char*);