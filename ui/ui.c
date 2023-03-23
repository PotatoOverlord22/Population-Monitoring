#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EXIT 0
#define DISPLAY_COUNTRIES_BY_NAME 1
#define DISPLAY_COUNTRIES_UP_TO_POPULATION 2
#define ADD_COUNTRY 3
#define REMOVE_COUNTRY 4
#define UPDATE_COUNTRY 5
#define DISPLAY_COUNTRIES_BY_CONTINENT 6
#define UNDO 7
#define REDO 8

UI* ui_create(Service* service) {
    UI* new_ui = malloc(sizeof(UI));
    new_ui->service = service;
    return new_ui;
}

void ui_destroy(UI* ui) {
    service_destroy(ui->service);
    free(ui);
}

void print_menu() {
    printf("\nMenu:");
    printf("\n\t1. Display countries containing a string");
    printf("\n\t2. Display countries up to a max population");
    printf("\n\t3. Add country");
    printf("\n\t4. Remove country");
    printf("\n\t5. Update country");
    printf("\n\t6. Display all countries on a given continent whose populations are greater than a given value");
    printf("\n\t7. Undo");
    printf("\n\t8. Redo");
    printf("\n\t0. EXIT");
}


void start_menu(UI* ui) {


    while (1) {
        print_menu();
        int user_option;
        read_user_option(&user_option);
        switch (user_option) {
            case EXIT:
                return;
            case DISPLAY_COUNTRIES_BY_NAME: {
                char country_name[50];
                printf("String: ");
                read_input_country_name(country_name, 50);
                int size;
                Country** countries = malloc(sizeof(Country) * service_get_repository_size(ui->service));
                service_get_countries_respecting_relation(ui->service, countries, &size, (void *) country_name,
                                                          (int (*)(Country*, void*)) containing_string);
                if (size == 0) {
                    printf("\nThere are no countries with such a name");
                    free(countries);
                    break;
                }
                char temporary_string[100];
                country_to_string(countries[0], temporary_string);
                printf("%d. %s", 1, temporary_string);
                for (int i = 1; i < size; ++i) {
                    country_to_string(countries[i], temporary_string);
                    printf("\n%d. %s", i + 1, temporary_string);
                }
                free(countries);
                break;
            }
            case ADD_COUNTRY: {
                char country_name[50];
                char country_continent[50];
                double population;
                printf("Country name: ");
                read_input_country_name(country_name, 50);
                printf("Continent: ");
                read_input_country_continent(country_continent, 50);
                printf("Population: ");
                read_input_country_population(&population);
                if (service_add_country(ui->service, country_name, country_continent, population))
                    printf("Country added successfully.");
                else
                    printf("Could not add country.");
                break;
            }
            case REMOVE_COUNTRY: {
                char country_name[50];
                printf("Country name: ");
                read_input_country_name(country_name, 50);
                if (service_remove_country_by_name(ui->service, country_name))
                    printf("Country %s removed successfully", country_name);
                else
                    printf("Could not remove country");
                break;
            }
            case UPDATE_COUNTRY: {
                print_update_country_submenu();
                int update_submenu_option;
                read_user_option(&update_submenu_option);
                switch (update_submenu_option) {
                    case 0:
                        break;
                    case 1: {
                        char country_name_to_search[50];
                        char country_new_name[50];
                        printf("Country name to update: ");
                        read_input_country_name(country_name_to_search, 50);
                        printf("Country new name: ");
                        read_input_country_name(country_new_name, 50);
                        if (service_update_country_name(ui->service, country_name_to_search, country_new_name))
                            printf("Update to name successful.");
                        else
                            printf("Update to name unsuccessful.");
                        break;
                    }
                    case 2: {
                        char country_name_to_search[50];
                        char country_new_continent[50];
                        printf("Country to update: ");
                        read_input_country_name(country_name_to_search, 50);
                        printf("Change continent to: ");
                        read_input_country_continent(country_new_continent, 50);
                        if (service_update_country_continent(ui->service, country_name_to_search,
                                                             country_new_continent))
                            printf("Update to continent successful.");
                        else
                            printf("Update to continent unsuccessful.");
                        break;
                    }
                    case 3: {
                        char country_name_to_search[50];
                        double new_population;
                        printf("Country to update: ");
                        read_input_country_name(country_name_to_search, 50);
                        printf("Change population to (millions): ");
                        read_input_country_population(&new_population);
                        if (service_update_country_population(ui->service, country_name_to_search, new_population)) {
                            printf("Successfully updated country population of %s", country_name_to_search);
                        } else
                            printf("Update to population unsuccessful.");
                        break;
                    }
                    case 4: {
                        char emigration_country_name[50];
                        char immigration_country_name[50];
                        double number_of_emigrants;
                        printf("Emigrant country: ");
                        read_input_country_name(emigration_country_name, 50);
                        printf("Immigrant country: ");
                        read_input_country_name(immigration_country_name, 50);
                        printf("Number of emigrants(in millions): ");
                        read_input_country_population(&number_of_emigrants);
                        if (service_modify_population_by_value(ui->service, emigration_country_name,
                                                               -number_of_emigrants)) {
                            printf("People successfully migrated.");
                            service_modify_population_by_value(ui->service, immigration_country_name,
                                                               number_of_emigrants);
                        } else
                            printf("Migration failed.");
                        break;
                    }
                    default:
                        printf("Unknown option");
                        break;
                }
                break;
            }
            case DISPLAY_COUNTRIES_BY_CONTINENT: {
                char continent[50];
                double min_population;
                int sorting_relation_choice;
                printf("Continent to look for (empty to skip): ");
                read_input_country_continent(continent, 50);
                printf("Minimum population: ");
                read_input_country_population(&min_population);
                printf("Sorting relation(0/1 <-> ascending/descending): ");
                read_input_int(&sorting_relation_choice);
                int (* sorting_relation)(double, double) = NULL;
                if (sorting_relation_choice == 0)
                    sorting_relation = ascending;
                else if (sorting_relation_choice == 1)
                    sorting_relation = descending;
                else {
                    printf("Bad sorting relation.");
                    break;
                }
                int size;
                Country** selected_countries = malloc(sizeof(Country) * service_get_repository_size(ui->service));
                service_get_countries_by_continent_and_min_population(ui->service, selected_countries, &size, continent,
                                                                      min_population, sorting_relation);
                if (size == 0) {
                    printf("\nThere are no countries satisfying continent name and/or population restrictions.");
                    free(selected_countries);
                    break;
                }
                char temporary_string[100];
                country_to_string(selected_countries[0], temporary_string);
                printf("%d. %s", 1, temporary_string);
                for (int i = 1; i < size; ++i) {
                    country_to_string(selected_countries[i], temporary_string);
                    printf("\n%d. %s", i + 1, temporary_string);
                }
                free(selected_countries);
                break;
            }
            case UNDO:{
                if (service_undo(ui->service))
                    printf("Undo successful");
                else
                    printf("No more undos!");
                break;
            }
            case REDO:{
                if (service_redo(ui->service))
                    printf("Redo successful");
                else
                    printf("No more redos!");
                break;
            }
            case DISPLAY_COUNTRIES_UP_TO_POPULATION:{
                printf("Population limit: ");
                double population_limit;
                read_input_double(&population_limit);
                int size;
                Country** countries = malloc(sizeof(Country) * service_get_repository_size(ui->service));
                service_get_countries_respecting_relation(ui->service, countries, &size, (void *) &population_limit,
                                                          (int (*)(Country*, void*)) max_population);
                if (size == 0) {
                    printf("\nThere are no countries with such a population limit.");
                    free(countries);
                    break;
                }
                char temporary_string[100];
                country_to_string(countries[0], temporary_string);
                printf("%d. %s", 1, temporary_string);
                for (int i = 1; i < size; ++i) {
                    country_to_string(countries[i], temporary_string);
                    printf("\n%d. %s", i + 1, temporary_string);
                }
                free(countries);
                break;
            }
            default:
                printf("Unknown option");
                break;
        }
    }
}

void read_user_option(int* user_option) {
    int clear_buffer;
    *user_option = -1;
    printf("\ninput > ");
    scanf("%d", user_option);
    while ((clear_buffer = getc(stdin)) != '\n');
}

void print_update_country_submenu() {
    printf("\t\t1. Update name");
    printf("\n\t\t2. Update continent");
    printf("\n\t\t3. Update population (no migration, negative population growth)");
    printf("\n\t\t4. Migration");
    printf("\n\t\t0. Exit submenu");
}

void read_input_country_name(char* country_name, int array_size) {
    fgets(country_name, array_size, stdin);
    country_name[strcspn(country_name, "\n")] = 0;
}

void read_input_country_continent(char* country_continent, int array_size) {
    fgets(country_continent, array_size, stdin);
    country_continent[strcspn(country_continent, "\n")] = 0;
}

void read_input_country_population(double* population) {
    scanf("%lf", population);
}

void read_input_int(int* user_int) {
    scanf("%d", user_int);
}

void read_input_double(double* user_double) {
    scanf("%lf", user_double);
}