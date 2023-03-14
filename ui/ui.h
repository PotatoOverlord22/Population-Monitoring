#pragma once

#include "../service/service.h"

typedef struct {
    Service* service;
} UI;

UI* create_ui(Service*);

void destroy_ui(UI*);

void print_menu();

void start_menu(UI*);

void read_input_country_name(char* country_continent, int array_size);

void read_input_country_continent(char* country_continent, int array_size);

void read_input_country_population(double* population);

