#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EXIT 0
#define DISPLAY_COUNTRIES 1
#define ADD_COUNTRY 2
#define REMOVE_COUNTRY 3
#define UPDATE_COUNTRY 4

UI* create_ui(Service* service) {
    UI* new_ui = malloc(sizeof(UI));
    new_ui->service = service;
    return new_ui;
}

void destroy_ui(UI* ui) {
    destroy_service(ui->service);
    free(ui);
}

void print_menu() {
    printf("\nMenu:");
    printf("\n\t1. Display countries containing a string");
    printf("\n\t2. Add country");
    printf("\n\t3. Remove country");
    printf("\n\t4. Update country");
    printf("\n\t0. EXIT");
}


void start_menu(UI* ui) {

    int user_option;
    int clear_buffer;
    while (1) {
        print_menu();
        user_option = -1;
        printf("\ninput > ");
        scanf("%d", &user_option);
        while ((clear_buffer = getc(stdin)) != '\n');
        switch (user_option) {
            case EXIT:
                return;
            case DISPLAY_COUNTRIES: {
                char country_name[256];
                printf("String: ");
                read_input_country_name(country_name, 256);
                int size;
                Country* countries = get_countries_containing_string(ui->service, country_name, &size);
                if (size == 0) {
                    printf("\nThere are no countries with such a name");
                    break;
                }
                char temp[256];
                country_to_string(&countries[0], temp);
                printf("%d. %s", 1, temp);
                for (int i = 1; i < size; ++i) {
                    country_to_string(&countries[i], temp);
                    printf("\n%d. %s", i + 1, temp);
                }
                free(countries);
                break;
            }
            case ADD_COUNTRY: {
                char country_name[256];
                char country_continent[256];
                double population;
                printf("Country name: ");
                read_input_country_name(country_name, 256);
                printf("Continent: ");
                read_input_country_continent(country_continent, 256);
                printf("Population: ");
                read_input_country_population(&population);
                if (add_country_service(ui->service, country_name, country_continent, population))
                    printf("Country added successfully.");
                else
                    printf("Could not add country.");
                break;
            }
            case REMOVE_COUNTRY: {
                char country_name[256];
                printf("Country name: ");
                read_input_country_name(country_name, 256);
                if (remove_country_by_name_service(ui->service, country_name))
                    printf("Country %s removed successfully", country_name);
                else
                    printf("Could not remove country");
                break;
            }
            case UPDATE_COUNTRY: {
                break;
            }
            default:
                printf("Unknown option");
        }
    }
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