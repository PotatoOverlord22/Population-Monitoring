#include "ui/ui.h"
int main() {
    Repository* repository = create_repository();
    Service* service = create_service(repository);
    initialize_hard_coded_countries(service);
    UI* ui = create_ui(service);
    start_menu(ui);

    destroy_ui(ui);
    return 0;
}