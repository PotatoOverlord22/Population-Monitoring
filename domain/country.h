#pragma once

typedef struct {
    char* name;
    char* continent;
    double population;
}Country;

Country *country_create(char* name, char* continent, double population);

void country_destroy(Country* country);

char* get_name(Country* country);

char* get_continent(Country* country);

double get_population(Country* country);

void set_name(Country*, char* new_name);

void set_continent(Country*, char* new_continent);

void set_population(Country*, double new_population);

void country_to_string(Country* country, char*string);