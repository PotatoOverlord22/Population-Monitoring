#include "repository.h"
#include <stdlib.h>
#include <string.h>

Repository* repository_create() {
    Repository* new_repository = malloc(sizeof(Repository));
    new_repository->data = (Country**) malloc(100 * sizeof(Country*));
    new_repository->size = 0;
    return new_repository;
}

void repository_destroy(Repository* repository) {
    for (int i = 0; i < repository->size; ++i)
        country_destroy(repository->data[i]);
    free(repository->data);
    free(repository);
}

Country** repository_get_all(Repository* repository) {
    return repository->data;
}

int repository_get_size(Repository* repository) {
    return repository->size;
}

int repository_find_country(Repository* repository, Country* country_to_find) {
    for (int i = 0; i < repository->size; ++i)
        if (strcmp(get_name(repository->data[i]), get_name(country_to_find)) == 0)
            return 1;
    return 0;
}

int repository_add_country(Repository* repository, Country* new_country) {
    /* Adds a country to the repository data
     * returns False if the country is already inside the data
     * returns True if the country was added successfully to the specified repository
     */
    if (repository_find_country(repository, new_country))
        return 0;
    repository->data[repository->size++] = new_country;
    return 1;
}

int repository_remove_country(Repository* repository, Country* country_to_remove) {
    /*
     *      Removes countries from the repository that have the same field values as country_to_remove
     *  returns -> True if at least one country was removed successfully
     *          -> False if the country was not in the repository in the first place.
     */
    int found = 0;
    for (int i = 0; i < repository->size; ++i) {
        if (strcmp(get_name(repository->data[i]), get_name(country_to_remove)) == 0 &&
                strcmp(get_continent(repository->data[i]), get_continent(country_to_remove)) == 0 &&
                get_population(repository->data[i]) == get_population(country_to_remove)) {

            set_name(repository->data[i], get_name(repository->data[repository->size - 1]));
            set_continent(repository->data[i], get_continent(repository->data[repository->size - 1]));
            set_population(repository->data[i], get_population(repository->data[repository->size - 1]));
            country_destroy(repository->data[repository->size - 1]);
            repository->size--;
            found = 1;
        }
    }
    return found;
}

int repository_remove_country_by_name(Repository* repository, char* name) {
    /*
     *      Removes countries from the repository that have the same name as the given string
     *  returns -> True if at least one country was removed successfully
     *          -> False if the country was not in the repository in the first place.
     */
    int found = 0;
    for (int i = 0; i < repository->size; ++i) {
        if (strcmp(get_name(repository->data[i]), name) == 0) {
            set_name(repository->data[i], get_name(repository->data[repository->size - 1]));
            set_continent(repository->data[i], get_continent(repository->data[repository->size - 1]));
            set_population(repository->data[i], get_population(repository->data[repository->size - 1]));
            country_destroy(repository->data[repository->size - 1]);
            repository->size--;
            found = 1;
        }
    }
    return found;
}