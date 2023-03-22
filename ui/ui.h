#pragma once

#include "../service/service.h"

typedef struct {
    Service* service;
} UI;

UI* ui_create(Service* service);

void ui_destroy(UI* ui);

void print_menu();

void print_update_country_submenu();

void start_menu(UI*);

void read_input_country_name(char* country_name, int array_size);

void read_input_country_continent(char* country_continent, int array_size);

void read_input_country_population(double* population);

void read_user_option(int* user_option);

void read_input_int(int* user_int);

