#include "repository.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

Repository* repository_create() {
    Repository* new_repository = malloc(sizeof(Repository));
    new_repository->data = vector_create(sizeof(Country*));
    return new_repository;
}

void repository_destroy(Repository* repository) {
    vector_destroy(repository->data, (void (*)(void*)) country_destroy);
    free(repository);
}

void** repository_get_all(Repository* repository) {
    return vector_get_all(repository->data);
}

int repository_get_size(Repository* repository) {
    return vector_get_size(repository->data);
}

int repository_find_country(Repository* repository, Country* country_to_find) {
    for (int i = 0; i < repository_get_size(repository); ++i)
        if (strcmp(get_name(vector_get_item(repository->data, i)), get_name(country_to_find)) == 0)
            return 1;
    return 0;
}

int repository_add_country(Repository* repository, Country* new_country) {
    /* Adds a country to the repository data
     * returns False if the country is already inside the data or if there is already a country with that name
     * returns True if the country was added successfully to the specified repository
     */
    if (repository_find_country(repository, new_country))
        return 0;
    vector_add_item(repository->data, new_country);
    return 1;
}

int repository_remove_country(Repository* repository, Country* country_to_remove) {
    /*
     *      Removes countries from the repository that have the same field values as country_to_remove
     *  returns -> True if at least one country was removed successfully
     *          -> False if the country was not in the repository in the first place.
     */
    int repository_size = repository_get_size(repository);
    for (int i = 0; i < repository_size; ++i) {
        if (strcmp(get_name(vector_get_item(repository->data, i)), get_name(country_to_remove)) == 0 &&
            strcmp(get_continent(vector_get_item(repository->data, i)), get_continent(country_to_remove)) == 0 &&
            get_population(vector_get_item(repository->data, i)) == get_population(country_to_remove)) {

            set_name(vector_get_item(repository->data, i),
                     get_name(vector_get_item(repository->data, repository_size - 1)));
            set_continent(vector_get_item(repository->data, i),
                          get_continent(vector_get_item(repository->data, repository_size - 1)));
            set_population(vector_get_item(repository->data, i),
                           get_population(vector_get_item(repository->data, repository_size - 1)));
            vector_remove_item(repository->data, repository_size - 1, country_destroy);
            return 1;
        }
    }
    return 0;
}

int repository_remove_country_by_name(Repository* repository, char* name) {
    /*
     *      Removes countries from the repository that have the same name as the given string
     *  returns -> True if at least one country was removed successfully
     *          -> False if the country was not in the repository in the first place.
     */
    int repository_size = repository_get_size(repository);
    for (int i = 0; i < repository_size; ++i) {
        if (strcmp(get_name(vector_get_item(repository->data, i)), name) == 0) {
            set_name(vector_get_item(repository->data, i),
                     get_name(vector_get_item(repository->data, repository_size - 1)));
            set_continent(vector_get_item(repository->data, i),
                          get_continent(vector_get_item(repository->data, repository_size - 1)));
            set_population(vector_get_item(repository->data, i),
                           get_population(vector_get_item(repository->data, repository_size - 1)));
            vector_remove_item(repository->data, repository_size - 1, country_destroy);
            return 1;
        }
    }
    return 0;
}

void repository_make_copy(Repository** destination_repository, Repository* source_repository) {
    *destination_repository = malloc(sizeof(Repository));
    if (*destination_repository == NULL)
        return;
    vector_make_copy(&(*destination_repository)->data, source_repository->data, (void (*)(void**, void*)) country_make_copy);
}