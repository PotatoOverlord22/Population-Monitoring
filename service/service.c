#include "service.h"
#include <stdlib.h>
#include <string.h>

Service* service_create(Repository* repository) {
    Service* new_service = malloc(sizeof(Service));
    new_service->repository = repository;
    return new_service;
}

void service_destroy(Service* service) {
    repository_destroy(service->repository);
    free(service);
}

int service_add_country(Service* service, char* name, char* continent, double population) {
    /*
     *  Adds a country to the repository inside the service
     * returns -> True if the country was added successfully
     *         -> False if country was already in repository
     */
    Country* new_country = country_create(name, continent, population);
    return repository_add_country(service->repository, new_country);
}

int service_remove_country(Service* service, char* name, char* continent, double population) {
    Country* country_to_remove = country_create(name, continent, population);
    return repository_remove_country(service->repository, country_to_remove);
}

Country** service_get_countries_containing_string(Service* service, char* substring, int* size) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    if (strcmp(substring, "") == 0) {
        *size = repository_get_size(service->repository);
        return all_countries;
    }
    Country** countries_with_string = malloc(sizeof(Country) * repository_get_size(service->repository));
    *size = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (strstr(get_name(all_countries[i]), substring) != 0) {
            countries_with_string[(*size)++] = all_countries[i];
        }
    }
    return countries_with_string;
}

void service_initialize_hard_coded_countries(Service* service) {
    service_add_country(service, "germany", "Europe", 223.02);
    service_add_country(service, "romania", "Europe", 19.3);
    service_add_country(service, "poland", "Europe", 50);
    service_add_country(service, "usa", "North America", 200.50);
    service_add_country(service, "mexico", "North America", 40.3);
    service_add_country(service, "brazil", "South America", 120);
    service_add_country(service, "china", "Asia", 2000);
    service_add_country(service, "japan", "Asia", 30);
    service_add_country(service, "india", "Asia", 2500);
    service_add_country(service, "zimbabwe", "Africa", 15);
}

int service_remove_country_by_name(Service* service, char* name) {
    return repository_remove_country_by_name(service->repository, name);
}

int service_update_country_name(Service* service, char* search_name, char* new_name) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    int found = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (strcmp(get_name(all_countries[i]), search_name) == 0) {
            set_name(all_countries[i], new_name);
            found = 1;
        }
    }
    return found;
}

int service_update_country_continent(Service* service, char* search_name, char* new_continent_name) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    int found = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (strcmp(get_name(all_countries[i]), search_name) == 0) {
            set_continent(all_countries[i], new_continent_name);
            found = 1;
        }
    }
    return found;
}

int service_update_country_population(Service* service, char* search_name, double new_population) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    int found = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (strcmp(get_name(all_countries[i]), search_name) == 0) {
            set_population(all_countries[i], new_population);
            found = 1;
        }
    }
    return found;
}

int service_modify_population_by_value(Service* service, char* search_name, double population_variation) {
    /*
     *      Adds or subtracts from the population of a searched country by a specified amount
     * service -> operates on this service's repository
     * search_name -> the name of the country we want to modify its population
     * population_variation -> positive/negative integer that represents the numeric change in population of a country
     *
     * return -> 1 if we successfully changed the population
     *        -> 0 if we failed, meaning we would've gotten a negative population by applying the population variation
     *               on the specified country
     */
    Country** all_countries = (Country**) repository_get_all(service->repository);
    int successful = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (strcmp(get_name(all_countries[i]), search_name) == 0) {
            if (get_population(all_countries[i]) + population_variation >= 0) {
                set_population(all_countries[i], get_population(all_countries[i]) + population_variation);
                successful = 1;
            }
        }
    }
    return successful;
}