#pragma once

typedef struct {
    char* name;
    char* continent;
    double population;
} Country;

Country* create_country(char* name, char* continent, double population);

void destroy_country(Country* country);

char* get_name(Country* country);

char* get_continent(Country* country);

double get_population(Country* country);

void country_to_string(Country* country, char* string);