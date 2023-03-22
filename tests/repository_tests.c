#include "../repository/repository.h"
#include <assert.h>

void repository_tests(){
    Repository* repository1 = repository_create();
    Country* country1 = country_create("test-name1", "test-continent1", 10);
    Country* country2 = country_create("test-name2", "test-continent2", 20);
    Country* country3 = country_create("test-name3", "test-continent3", 30);
    Country* country4 = country_create("test-name4", "test-continent4", 40);
    Country* country5 = country_create("not in repo", "", 0);

    repository_add_country(repository1, country1);
    assert(repository_get_size(repository1) == 1);
    repository_add_country(repository1, country2);
    repository_add_country(repository1, country3);
    repository_add_country(repository1, country4);
    assert(repository_get_size(repository1) == 4);
    assert(repository_find_country(repository1, country1));
    assert(!repository_find_country(repository1, country5));

    assert(repository_remove_country(repository1, country2));
    assert(repository_get_size(repository1) == 3);

    Repository* repository_copy;
    repository_make_copy(&repository_copy, repository1);
    assert(repository_get_size(repository1) == repository_get_size(repository_copy));
    void** original_elements = repository_get_all(repository1);
    void** copied_elements = repository_get_all(repository_copy);
    for (int i = 0; i < repository_get_size(repository1); ++i)
        assert(original_elements[i] != copied_elements[i]);

    repository_destroy(repository1);
    repository_destroy(repository_copy);
    country_destroy(country5);
}