#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void delete_field(struct table *table_given) {
    // variable to hold the field name to be deleted
    char field_name[32];
    // incrementor variables
    int i;
    int n;
    int y;
    // get the name of the array to be deleted
    printf("Enter the name of the field you would like to delete: ");
    scanf("%s", &field_name);
    // all of these for loops work the same so I will only comment one
    // for every field of type string
    for (i = 0; i < table_given->num_str; i++) {
        // if the current field is the one to be deleted
        if (strcmp(table_given->stringfields[i]->field_name, field_name) == 0) {
            // create new fields array and allocate it some memory
            struct str_field **fields =
                    malloc(sizeof(table_given->stringfields) - sizeof(struct str_field));
            // free the field to be deleted
            free(table_given->stringfields[i]->values);
            free(table_given->stringfields[i]);
            // set new fields array to the same contents as the old fields array
            // but without the field to be deleted
            for (n = 0, y = 0; n < table_given->num_str; y++, n++) {
                if (n == i) {
                    y--;
                } else {
                    fields[y] = table_given->stringfields[n];
                }
            }
            // free the old fields array
            free(table_given->stringfields);
            // set the new fields array to replace the old one
            table_given->stringfields = fields;
            // decrement the number of fields
            table_given->num_str--;
        }
    }
    for (i = 0; i < table_given->num_int; i++) {
        if (strcmp(table_given->intergerfields[i]->field_name, field_name)
            == 0) {
            struct int_field **fields =
                    malloc(sizeof(table_given->intergerfields) - sizeof(struct int_field));
            free(table_given->intergerfields[i]->values);
            free(table_given->intergerfields[i]);
            for (n = 0, y = 0; n < table_given->num_int; y++, n++) {
                if (n == i) {
                    y--;
                } else {
                    fields[y] = table_given->intergerfields[n];
                }
            }
            free(table_given->intergerfields);
            table_given->intergerfields = fields;
            table_given->num_int--;
        }
    }
    for (i = 0; i < table_given->num_bool; i++) {
        if (strcmp(table_given->booleanfields[i]->field_name, field_name)
            == 0) {
            struct bool_field **fields =
                    malloc(sizeof(table_given->booleanfields) - sizeof(struct bool_field));
            free(table_given->booleanfields[i]->values);
            free(table_given->booleanfields[i]);
            for (n = 0, y = 0; n < table_given->num_bool; y++, n++) {
                if (n == i) {
                    y--;
                } else {
                    fields[y] = table_given->booleanfields[n];
                }
            }
            free(table_given->booleanfields);
            table_given->booleanfields = fields;
            table_given->num_bool--;
        }
    }
    for (i = 0; i < table_given->num_float; i++) {
        if (strcmp(table_given->floatingfields[i]->field_name, field_name)
            == 0) {
            struct float_field **fields =
                    malloc(sizeof(table_given->floatingfields) - sizeof(struct float_field));
            free(table_given->floatingfields[i]->values);
            free(table_given->floatingfields[i]);
            for (n = 0, y = 0; n < table_given->num_float; y++, n++) {
                if (n == i) {
                    y--;
                } else {
                    fields[y] = table_given->floatingfields[n];
                }
            }
            free(table_given->floatingfields);
            table_given->floatingfields = fields;
            table_given->num_float--;
        }
    }
}
