#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void delete_record(struct table *table_given) {
    // variable to hold the number of the record to delete
    int num_to_delete;
    // incrementor variables
    int i;
    int n;
    int y;
    // get the new value from the user
    printf("\nEnter the number of record you would like to delete: ");
    scanf("%d", &num_to_delete);
    // decrement the number of records
    table_given->num_of_records--;
    // each of these for loops work the same way so I shall only comment
    // the first one
    // for every field of type string
    for (i = 0; i < table_given->num_str; i++) {
        // pointer to the curreent field
        struct str_field *field = table_given->stringfields[i];
        // variable to hold the new values array
        char (*new_values)[128];
        // allocate memory to the new_values array
        new_values = malloc(sizeof(char) * (field->num_of_values - 1) * 128);
        // sets the new_values array to the same as the old one but
        // without
        // the value for the record beign removed
        for (n = 0, y = 0; n < field->num_of_values; y++, n++) {
            if (n == num_to_delete) {
                y--;
            } else {
                strcpy (new_values[y], field->values[n]);
            }
        }
        // decrement the number fo values in the field
        field->num_of_values--;
        // deallocate memory from the old values array
        free(field->values);
        // replace the old values array with the new one
        field->values = new_values;
    }
    for (i = 0; i < table_given->num_int; i++) {
        struct int_field *field = table_given->intergerfields[i];
        int *new_values;
        new_values = malloc(sizeof(int) * (field->num_of_values - 1));
        for (n = 0, y = 0; n < field->num_of_values; y++, n++) {
            if (n == num_to_delete) {
                y--;
            } else {
                new_values[y] = field->values[n];
            }
        }
        field->num_of_values--;
        free(field->values);
        field->values = new_values;
    }
    for (i = 0; i < table_given->num_bool; i++) {
        struct bool_field *field = table_given->booleanfields[i];
        bool *new_values;
        new_values = malloc(sizeof(bool) * (field->num_of_values - 1));
        for (n = 0, y = 0; n < field->num_of_values; y++, n++) {
            if (n == num_to_delete) {
                y--;
            } else {
                new_values[y] = field->values[n];
            }
        }
        field->num_of_values--;
        free(field->values);
        field->values = new_values;
    }
    for (i = 0; i < table_given->num_float; i++) {
        struct float_field *field = table_given->floatingfields[i];
        float *new_values;
        new_values = malloc(sizeof(float) * (field->num_of_values - 1));
        for (n = 0, y = 0; n < field->num_of_values; y++, n++) {
            if (n == num_to_delete) {
                y--;
            } else {
                new_values[y] = field->values[n];
            }
        }
        field->num_of_values--;
        free(field->values);
        field->values = new_values;
    }
}
