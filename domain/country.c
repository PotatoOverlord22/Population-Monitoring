#include "country.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Country* create_country(char* name, char* continent, double population) {
    Country* new_country = malloc(sizeof(Country));
    new_country->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    new_country->continent = (char*) malloc((strlen(continent) + 1) * sizeof(char));
    new_country->population = population;
    strcpy(new_country->name, name);
    strcpy(new_country->continent, continent);
    return new_country;
}

void destroy_country(Country* country) {
    free(country->name);
    free(country->continent);
    free(country);
}

char* get_name(Country* country) {
    return country->name;
}

char* get_continent(Country* country) {
    return country->continent;

}

double get_population(Country* country) {
    return country->population;
}

void country_to_string(Country* country, char* string){
    sprintf(string, "%s in continent %s with population %lf millions", country->name, country->continent, country->population);
}