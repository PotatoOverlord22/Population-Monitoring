#pragma once

#include "../repository/repository.h"

typedef struct {
    Repository* repository;
} Service;

Service* service_create(Repository* repository);

void service_destroy(Service* service);

int service_add_country(Service* service, char* name, char* continent, double population);

int service_remove_country(Service* service, char* name, char* continent, double population);

void service_get_countries_containing_string(Service* service, Country** countries_with_string, char* substring, int* size);

void
service_get_countries_by_continent_and_min_population(Service* service, Country*** selected_countries,
                                                      char* searched_continent, double min_population,
                                                      int (* sort_relation)(Country*, Country*));

void service_initialize_hard_coded_countries(Service* service);

int service_remove_country_by_name(Service* service, char* name);

int service_update_country_name(Service* service, char* search_name, char* new_name);

int service_update_country_continent(Service* service, char* search_name, char* new_continent_name);

int service_update_country_population(Service* service, char* search_name, double new_population);

int service_modify_population_by_value(Service* service, char* search_name, double population_variation);

int service_get_repository_size(Service* service);