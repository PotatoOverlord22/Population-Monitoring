#include "service.h"
#include <stdlib.h>
#include <string.h>

Service* create_service(Repository* repository) {
    Service* new_service = malloc(sizeof(Service));
    new_service->repository = repository;
    return new_service;
}

void destroy_service(Service* service) {
    destroy_repository(service->repository);
    free(service);
}

int add_country_service(Service* service, char* name, char* continent, double population) {
    /*
     *  Adds a country to the repository inside the service
     * returns -> True if the country was added successfully
     *         -> False if country was already in repository
     */
    Country* new_country = create_country(name, continent, population);
    return add_country(service->repository, new_country);
}

int remove_country_service(Service* service, char* name, char* continent, double population) {
    Country* country_to_remove = create_country(name, continent, population);
    return remove_country(service->repository, country_to_remove);
}

void update_country_service(Service*, Country*);

Country** get_countries_containing_string(Service* service, char* substring, int* size) {
    if (strcmp(substring, "") == 0) {
        *size = get_size(service->repository);
        return get_all(service->repository);
    }
    Country** countries = malloc(sizeof(Country) * get_size(service->repository));
    *size = 0;
    for (int i = 0; i < get_size(service->repository); ++i) {
        if (strstr(get_name(service->repository->data[i]), substring) != 0) {
            countries[(*size)++] = service->repository->data[i];
        }
    }
    return countries;
}

void initialize_hard_coded_countries(Service* service) {
    add_country_service(service, "germany", "Europe", 223.02);
    add_country_service(service, "romania", "Europe", 19.3);
    add_country_service(service, "poland", "Europe", 50);
    add_country_service(service, "usa", "North America", 200.50);
    add_country_service(service, "mexico", "North America", 40.3);
    add_country_service(service, "brazil", "South America", 120);
    add_country_service(service, "china", "Asia", 2000);
    add_country_service(service, "japan", "Asia", 30);
    add_country_service(service, "india", "Asia", 2500);
    add_country_service(service, "zimbabwe", "Africa", 15);
}

int remove_country_by_name_service(Service* service, char* name) {
    return remove_country_by_name(service->repository, name);
}

int update_country_name(Service* service, char* search_name, char* new_name) {
    int found = 0;
    for (int i = 0; i < get_size(service->repository); ++i) {
        if (strcmp(get_name(service->repository->data[i]), search_name) == 0) {
            strcpy(service->repository->data[i]->name, new_name);
            found = 1;
        }
    }
    return found;
}

int update_country_continent(Service* service, char* search_name, char* new_continent) {
    int found = 0;
    for (int i = 0; i < get_size(service->repository); ++i) {
        if (strcmp(get_name(service->repository->data[i]), search_name) == 0) {
            strcpy(service->repository->data[i]->continent, new_continent);
            found = 1;
        }
    }
    return found;
}

int update_country_population(Service* service, char* search_name, double new_population) {
    int found = 0;
    for (int i = 0; i < get_size(service->repository); ++i) {
        if (strcmp(get_name(service->repository->data[i]), search_name) == 0) {
            service->repository->data[i]->population = new_population;
            found = 1;
        }
    }
    return found;
}

int add_population_to_country(Service* service, char* search_name, double additional_population){
    int successful = 0;
    for (int i = 0; i < get_size(service->repository); ++i) {
        if (strcmp(get_name(service->repository->data[i]), search_name) == 0) {
            if (service->repository->data[i]->population + additional_population >= 0){
                service->repository->data[i]->population += additional_population;
                successful = 1;
            }
        }
    }
    return successful;
}