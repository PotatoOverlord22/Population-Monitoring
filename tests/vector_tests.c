#include "../repository/vector.h"
#include <stdio.h>
#include <assert.h>

void vector_tests() {
    Country* country1 = country_create("test-name1", "test-continent1", 50.01);
    Country* country2 = country_create("test-name2", "test-continent2", 70.02);
    Country* country3 = country_create("test-name3", "test-continent3", 90.03);
    Vector* vector1 = vector_create(sizeof(Country*));

    vector_add_item(vector1, country1);
    vector_add_item(vector1, country2);
    vector_add_item(vector1, country3);
    assert(vector_get_size(vector1) == 3);
    assert(vector_get_item(vector1, 0) == country1);
    assert(vector_get_item(vector1, 1) == country2);
    assert(vector_get_item(vector1, 2) == country3);
    assert(vector_get_item(vector1, 10) == NULL);
    assert(vector_get_item(vector1, -1) == NULL);

    assert(vector_remove_item(vector1, 0, country_destroy));
    assert(vector_get_size(vector1) == 2);
    assert(vector_get_item(vector1, 0) == country2);
    assert(vector_get_item(vector1, 1) == country3);
    assert(vector_get_item(vector1, 2) == NULL);

    Vector* vector_copy;
    vector_make_copy(&vector_copy, vector1, (void (*)(void**, void*)) country_make_copy);
    assert(vector_get_size(vector_copy) == 2);
    assert(vector_get_item(vector_copy, 0) != vector_get_item(vector1, 0));
    assert(vector_get_item(vector_copy, 1) != country3);
    assert(vector_get_item(vector1, 2) == NULL);


    vector_destroy(vector1, (void (*)(void*)) country_destroy);
    vector_destroy(vector_copy, (void (*)(void*)) country_destroy);
}
