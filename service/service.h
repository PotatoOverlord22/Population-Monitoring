#pragma once

#include "../repository/repository.h"

typedef struct {
    Repository* repository;
} Service;

Service* service_create(Repository* repository);

void service_destroy(Service* service);

int service_add_country(Service* service, char* name, char* continent, double population);

int service_remove_country(Service* service, char* name, char* continent, double population);

Country** service_get_countries_containing_string(Service* service, char* substring, int* size);

void service_initialize_hard_coded_countries(Service* service);

int service_remove_country_by_name(Service* service, char* name);

int service_update_country_name(Service* service, char* search_name, char* new_name);

int service_update_country_continent(Service* service, char* search_name, char* new_continent_name);

int service_update_country_population(Service* service, char* search_name, double new_population);

int service_modify_population_by_value(Service* service, char* search_name, double population_variation);