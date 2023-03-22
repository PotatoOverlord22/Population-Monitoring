#include "../domain/country.h"
#include "country_tests.h"
#include <assert.h>
#include <string.h>


void country_tests() {
    Country* country1 = country_create("test-name", "test-continent", 100.02);
    assert(strcmp(country1->name, "test-name") == 0);
    assert(strcmp(country1->continent, "test-continent") == 0);
    assert(country1->population == 100.02);

    assert(strcmp(get_name(country1), "test-name") == 0);
    assert(strcmp(get_continent(country1), "test-continent") == 0);
    assert(get_population(country1) == 100.02);

    set_name(country1, "test-name2");
    set_continent(country1, "test-continent2");
    set_population(country1, 2);

    assert(strcmp(country1->name, "test-name2") == 0);
    assert(strcmp(country1->continent, "test-continent2") == 0);
    assert(country1->population == 2);

    assert(strcmp(get_name(country1), "test-name2") == 0);
    assert(strcmp(get_continent(country1), "test-continent2") == 0);
    assert(get_population(country1) == 2);

    char temp[100];
    country_to_string(country1, temp);
    assert(strcmp(temp, "test-name2 in continent test-continent2 with population 2.00 millions") == 0);

    Country* country1_copy;
    country_make_copy(&country1_copy, country1);
    assert(country1 != country1_copy);
    assert(get_name(country1) != get_name(country1_copy));
    assert(get_continent(country1) != get_continent(country1_copy));
    assert(get_population(country1) == get_population(country1_copy));
    assert(strcmp(get_name(country1), get_name(country1_copy)) == 0);
    assert(strcmp(get_continent(country1), get_continent(country1_copy)) == 0);

    set_name(country1, "should be different than copy");
    set_continent(country1, "diff than copy");
    assert(strcmp(get_name(country1), get_name(country1_copy)) != 0);
    assert(strcmp(get_continent(country1), get_continent(country1_copy)) != 0);

    country_destroy(country1);
    country_destroy(country1_copy);
}