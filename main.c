#include "ui/ui.h"
int main() {
    Repository* repository = repository_create();
    Service* service = service_create(repository);
    service_initialize_hard_coded_countries(service);
    UI* ui = create_ui(service);
    start_menu(ui);

    destroy_ui(ui);
    return 0;
}