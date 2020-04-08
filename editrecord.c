#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void edit_record(struct table *table_given) {
    // variable to hold number of the record to be edited
    int record_num;
    // variable to hold the name of the field to edit
    char field_name[32];
    // incrementor variable
    int i;
    char c;
    // get the number of the record to be edited
    printf("Enter the number of the record you would like to change: ");
    scanf("%d", &record_num);
    // tell the user if the record does not exist and exit
    if (table_given->num_of_records == record_num || record_num < 0) {
        printf("Record does not exist.");
        return;
    }
    // get the name of the field the user wnats to edit
    printf("Enter the name of the field you would like to edit: ");
    scanf("%s", &field_name);
    // for every field of type string
    for (i = 0; i < table_given->num_str; i++) {
        // if current field is the one the user wnats to edit
        if (strcmp(table_given->stringfields[i]->field_name, field_name) == 0) {
            // pointer to the field for short hand
            struct str_field *field = table_given->stringfields[i];
            // holds new value before it is set
            char new_value[128];
            // gets the new value
            printf("Enter new value for field %s of type string: ", &field_name);
            scanf("%s", new_value);
            // copy the new value into the field
            strcpy (field->values[record_num], new_value);
        }
    }
    // for every field of type interger
    for (i = 0; i < table_given->num_int; i++) {
        // if the current field is the one the user wnats to edit
        if (strcmp(table_given->intergerfields[i]->field_name, field_name)
            == 0) {
            // pointer to field for short hand
            struct int_field *field = table_given->intergerfields[i];
            // variable to hold the new value
            int new_value;
            while (true) {
                printf("Enter new value for field %s of type interger: ", &field_name);
                if (scanf("%d", &new_value) == 1) {
                    break;
                } else {
                    printf("You did nto enter an interger, try again!");
                }
                while ((c = getchar()) != '\n' && c != EOF);
            }
            // sets the new value
            field->values[record_num] = new_value;
        }
    }
    // for every field of type boolean
    for (i = 0; i < table_given->num_bool; i++) {
        // of the current field is the one the user wnats to edit
        if (strcmp(table_given->booleanfields[i]->field_name, field_name)
            == 0) {
            // pointer to field for short hand
            struct bool_field *field = table_given->booleanfields[i];
            // variable to hold the new input from the user
            char new_value_input[8];
            // while loop for verification perposes
            while (true) {
                // get the new value from the user
                printf("Enter new value for field %s of type boolean: ", field_name);
                scanf("%s", &new_value_input);
                // if statement to decode the users input and set the new
                // value
                if (tolower(new_value_input[0]) == 'y' || tolower(new_value_input[0]) == 't') {
                    field->values[record_num] = true;
                    break;
                } else if (tolower(new_value_input[0]) == 'n' || tolower(new_value_input[0]) == 'f') {
                    field->values[record_num] = false;
                    break;
                } else {
                    // if the user did not enter an interger then tell
                    // them
                    printf("You did not enter a boolean. Try again.");
                }
            }
        }
    }
    // for every field of type float
    for (i = 0; i < table_given->num_float; i++) {
        // if the current field is the one the user wnats to edit
        if (strcmp(table_given->floatingfields[i]->field_name, field_name)
            == 0) {
            // pointer to the field the user wants to edit for short hand
            struct float_field *field = table_given->floatingfields[i];
            // variable to hold the new value
            float new_value;
            char c;
            while (true) {
                printf("Enter new value for field %s of type float: ", field_name);
                if (scanf("%f", &new_value) == 1) {
                    break;
                } else {
                    printf("You did not enter a number, try again!\n");
                }
                while ((c = getchar()) != '\n' && c != EOF);
            }
            // set the new value
            field->values[record_num] = new_value;
        }
    }
}
