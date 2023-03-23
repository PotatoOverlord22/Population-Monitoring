#include "../service/service.h"
#include <assert.h>

void service_tests(){
    Repository* repository1 = repository_create();
    Service* service1 = service_create(repository1);
    service_add_country(service1, "test-name1", "test-continent1", 10.01);
    service_add_country(service1, "test-name2", "test-continent2", 20.02);
    assert(service_get_repository_size(service1) == 2);
    service_remove_country_by_name(service1, "test-name1");
    assert(!service_remove_country_by_name(service1, "not in repo"));
    assert(service_get_repository_size(service1) == 1);
    service_update_country_name(service1, "test-name2", "new-test-name2");

    service_destroy(service1);
}