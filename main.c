#include "ui/ui.h"
#include "tests/country_tests.h"
#include "tests/repository_tests.h"
#include "tests/vector_tests.h"
#include "tests/service_tests.h"


int main() {
    country_tests();
    vector_tests();
    repository_tests();
    service_tests();

//    Repository* repository = repository_create();
//    Service* service = service_create(repository);
//    service_initialize_hard_coded_countries(service);
//    UI* ui = ui_create(service);
//    start_menu(ui);
//
//    ui_destroy(ui);
    return 0;
}