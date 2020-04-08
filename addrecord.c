#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_record(struct table *table_given) {
    // incrementor interger
    int i;
    char c;
    // incrment number of records
    table_given->num_of_records++;
    // for loops to get values for the new record
    for (i = 0; i < table_given->num_str; i++) {
        // get pointer to field for shorthand
        struct str_field *field = table_given->stringfields[i];
        // increment number of values in field
        field->num_of_values++;
        // increase memory allocation of the array
        field->values = realloc(field->values, sizeof(field->values) + sizeof(char) * 128);
        // ask user for new value and set it
        printf("\nEnter value for field %s of type string: ", field->field_name);
        scanf("%s", field->values[table_given->num_of_records - 1]);
    }
    for (i = 0; i < table_given->num_int; i++) {
        // get pointer to field for shorthand
        struct int_field *field = table_given->intergerfields[i];
        // increment number of values
        field->num_of_values++;
        // get more memory for values in field
        field->values = realloc(field->values, sizeof(field->values) + sizeof(int));
        while (true) {
            printf("\nEnter value for field %s of type interger: ", field->field_name);
            if (scanf("%d", &field->values[table_given->num_of_records - 1]) == 1) {
                break;
            } else {
                printf("You did not enter an interger, try again!\n");
            }
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    for (i = 0; i < table_given->num_bool; i++) {
        // get pointer to field for shorthand
        struct bool_field *field = table_given->booleanfields[i];
        // get more memory for values in field
        field->values = realloc(field->values, sizeof(field->values) + sizeof(bool));
        // increment number of values
        field->num_of_values++;
        // while loop for verification perposes
        while (true) {
            // get new value from user
            printf("\nEnter value for field %s of type boolean: ", field->field_name);
            // variable to hold input
            char input[8];
            // get input from user
            scanf("%s", input);
            // if statement to determine of onput is true or false and set
            //
            // value accordingly
            if (tolower(input[0]) == 't' || tolower(input[0]) == 'y') {
                field->values[table_given->num_of_records - 1] = true;
                break;
            } else if (tolower(input[0]) == 'f' || tolower(input[0]) == 'y') {
                field->values[table_given->num_of_records - 1] = false;
                break;
            } else {
                // tell the user if they did not enter a valid input
                printf("You did not enter a boolean value. Try again.");
            }
        }
    }
    for (i = 0; i < table_given->num_float; i++) {
        // get pointer to field for shorthand
        struct float_field *field = table_given->floatingfields[i];
        // increment number of values in field
        field->num_of_values++;
        // allocate more memory for values in the field
        field->values = realloc(field->values, sizeof(field->values) + sizeof(float));
        while (true) {
            printf("\nEnter value for field %s of type float: ", field->field_name);
            if (scanf("%f", &field->values[table_given->num_of_records - 1]) == 1) {
                break;
            } else {
                printf("You did not enter a number, try again!\n");
            }
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
