#include "country.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Country* country_create(char* name, char* continent, double population) {
    Country* new_country = malloc(sizeof(Country));
    new_country->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    new_country->continent = (char*) malloc((strlen(continent) + 1) * sizeof(char));
    new_country->population = population;
    strcpy(new_country->name, name);
    strcpy(new_country->continent, continent);
    return new_country;
}

void country_destroy(Country* country) {
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

void set_name(Country* country, char* new_name){
    if (country->name == new_name)
        return;
    if (strlen(new_name) > strlen(country->name)){
        free(country->name);
        char* resized_name = (char*) malloc((strlen(new_name) + 1) * sizeof(char));
        country->name = resized_name;
    }
    strcpy(country->name, new_name);

}

void set_continent(Country* country, char* new_continent){
    if (country->continent == new_continent)
        return;
    if (strlen(new_continent) > strlen(country->continent)){
        free(country->continent);
        char* resized_name = (char*) malloc((strlen(new_continent) + 1) * sizeof(char));
        country->continent = resized_name;
    }
    strcpy(country->continent, new_continent);
}

void set_population(Country* country, double new_population){
    country->population = new_population;
}

void country_to_string(Country* country, char* string){
    sprintf(string, "%s in continent %s with population %lf millions", country->name, country->continent, country->population);
}