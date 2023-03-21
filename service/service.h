#pragma once

#include "../repository/repository.h"

typedef struct {
    Repository* repository;
} Service;

Service* create_service(Repository* repository);

void destroy_service(Service* service);

int add_country_service(Service* service, char* name, char* continent, double population);

int remove_country_service(Service* service, char* name, char* continent, double population);

void update_country_service(Service*, Country*);

Country** get_countries_containing_string(Service* service, char* substring, int* size);

void initialize_hard_coded_countries(Service*);

int remove_country_by_name_service(Service*, char*);

int update_country_name(Service*, char* search_name, char* new_name);

int update_country_continent(Service*, char* search_name, char* new_continent_name);

int update_country_population(Service* service, char* search_name, double new_population);

int modify_population_by_value(Service* service, char* search_name, double population_variation);