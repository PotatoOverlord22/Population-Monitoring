#include "service.h"
#include <stdlib.h>
#include <string.h>

Service* service_create(Repository* repository) {
    Service* new_service = malloc(sizeof(Service));
    new_service->repository = repository;
    new_service->undo = undo_create();
    new_service->redo = redo_create();
    return new_service;
}

void service_destroy(Service* service) {
    repository_destroy(service->repository);
    undo_destroy(service->undo);
    redo_destroy(service->redo);
    free(service);
}

int service_add_country(Service* service, char* name, char* continent, double population) {
    /*
     *  Adds a country to the repository inside the service
     * returns -> True if the country was added successfully
     *         -> False if country was already in repository
     */
    undo_add(service->undo, service->repository);
    Country* new_country = country_create(name, continent, population);
    return repository_add_country(service->repository, new_country);
}

int service_remove_country(Service* service, char* name, char* continent, double population) {
    undo_add(service->undo, service->repository);
    Country* country_to_remove = country_create(name, continent, population);
    return repository_remove_country(service->repository, country_to_remove);
}

void
service_get_countries_respecting_relation(Service* service, Country** countries_respecting_relation, int* size, void* restriction, int (*relation)(Country*, void*)) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    *size = 0;
    for (int i = 0; i < repository_get_size(service->repository); ++i) {
        if (relation(all_countries[i], restriction)) {
            countries_respecting_relation[(*size)++] = all_countries[i];
        }
    }
}

void
service_get_countries_by_continent_and_min_population(Service* service, Country** selected_countries, int* size,
                                                      char* searched_continent, double min_population,
                                                      int (* sort_relation)(double, double)) {
    Country** all_countries = (Country**) repository_get_all(service->repository);
    *size = 0;
    if (strcmp(searched_continent, "") == 0) {
        for (int i = 0; i < repository_get_size(service->repository); ++i) {
            if (get_population(all_countries[i]) > min_population) {
                selected_countries[(*size)++] = all_countries[i];
            }
        }
    } else {
        for (int i = 0; i < repository_get_size(service->repository); ++i) {
            if (get_population(all_countries[i]) > min_population &&
                strcmp(get_continent(all_countries[i]), searched_continent) == 0) {
                selected_countries[(*size)++] = all_countries[i];
            }
        }
    }
    for (int i = 0; i < (*size) - 1; ++i) {
        for (int j = i + 1; j < *size; ++j)
            if (!sort_relation(get_population(selected_countries[i]), get_population(selected_countries[j]))) {
                service_swap_country_fields(selected_countries[i], selected_countries[j]);
            }
    }
}

void service_initialize_hard_coded_countries(Service* service) {
    repository_add_country(service->repository, country_create("germany", "europe", 223.02));
    repository_add_country(service->repository, country_create("romania", "europe", 19.3));
    repository_add_country(service->repository, country_create("poland", "europe", 50));
    repository_add_country(service->repository, country_create("usa", "north america", 200.50));
    repository_add_country(service->repository, country_create("mexico", "north america", 40.3));
    repository_add_country(service->repository, country_create("brazil", "south america", 120));
    repository_add_country(service->repository, country_create("china", "asia", 2000));
    repository_add_country(service->repository, country_create("japan", "asia", 30));
    repository_add_country(service->repository, country_create("india", "asia", 2500));
    repository_add_country(service->repository, country_create("zimbabwe", "africa", 15));
}

int service_remove_country_by_name(Service* service, char* name) {
    undo_add(service->undo, service->repository);
    return repository_remove_country_by_name(service->repository, name);
}

int service_update_country_name(Service* service, char* search_name, char* new_name) {
    undo_add(service->undo, service->repository);
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
    undo_add(service->undo, service->repository);
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
    undo_add(service->undo, service->repository);
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
    //undo_add(service->undo, service->repository);
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

int service_get_repository_size(Service* service) {
    return repository_get_size(service->repository);
}

int descending(double first, double second) {
    return first > second;
}

int ascending(double first, double second) {
    return first < second;
}

int max_population(Country* country, const double* max_population){
    if(get_population(country) <= *max_population)
        return 1;
    return 0;
}

int containing_string(Country* country, char* substring){
    if (strcmp(substring, "") == 0)
        return 1;
    if (strstr(get_name(country), substring) == NULL)
        return 0;
    return 1;
}

void service_swap_country_fields(Country* first_country, Country* second_country) {
    char temp_name[strlen(get_name(first_country)) + 1];
    char temp_continent[strlen(get_continent(first_country)) + 1];
    double temp_population;
    strcpy(temp_name, get_name(first_country));
    strcpy(temp_continent, get_continent(first_country));
    temp_population = get_population(first_country);
    set_name(first_country, get_name(second_country));
    set_name(second_country, temp_name);
    set_continent(first_country, get_continent(second_country));
    set_continent(second_country, temp_continent);
    set_population(first_country, get_population(second_country));
    set_population(second_country, temp_population);
}

int service_undo(Service* service){
    return undo(service->undo, &service->repository, service->redo);
}

int service_redo(Service* service){
    return redo(service->redo, &service->repository, service->undo);
}