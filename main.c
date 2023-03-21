#include "ui/ui.h"
int main() {
    Repository* repository = repository_create();
    Service* service = service_create(repository);
    service_initialize_hard_coded_countries(service);
    UI* ui = ui_create(service);
    start_menu(ui);

    ui_destroy(ui);
    return 0;
}