#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
display_record(struct table *table_given, int record_num) {
    int i;
    printf("\nDisplaying record %d:", record_num);
    for (i = 0; i < table_given->num_str; i++) {
        struct str_field *field = table_given->stringfields[i];
        printf("\n%s: %s", field->field_name, field->values[record_num]);
    }
    for (i = 0; i < table_given->num_int; i++) {
        struct int_field *field = table_given->intergerfields[i];
        printf("\n%s: %d", field->field_name, field->values[record_num]);
    }
    for (i = 0; i < table_given->num_bool; i++) {
        struct bool_field *field = table_given->booleanfields[i];
        if (field->values[record_num] == true) {
            printf("\n%s: true", field->field_name);
        } else {
            printf("\n%s: false", field->field_name);
        }
    }
    for (i = 0; i < table_given->num_float; i++) {
        struct float_field *field = table_given->floatingfields[i];
        printf("\n%s: %f", field->field_name, field->values[record_num]);
    }
}

void
search_str(struct table *table_given, int field_num) {
    struct str_field *field = table_given->stringfields[field_num];
    int i;
    char value_to_search[128];
    printf("\nThe type of the selected field is string. Enter value to search for: ");
    scanf("%s", &value_to_search);
    printf("\nMatching records: \n");
    for (i = 0; i < field->num_of_values; i++) {
        if (strcmp(field->values[i], value_to_search) == 0) {
            display_record(table_given, i);
        }
    }
}

void
search_int(struct table *table_given, int field_num) {
    struct int_field *field = table_given->intergerfields[field_num];
    int i;
    int value_to_search;
    printf("\nThe type of the selected field is interger. Enter value to search for: ");
    scanf("%d", &value_to_search);
    printf("\nMatching records: \n");
    for (i = 0; i < field->num_of_values; i++) {
        if (field->values[i] == value_to_search) {
            display_record(table_given, i);
        }
    }
}

void
search_bool(struct table *table_given, int field_num) {
    struct bool_field *field = table_given->booleanfields[field_num];
    int i;
    bool value_to_search;
    char input_value[8];
    while (true) {
        printf("\nThe type of the selected field is boolean. Enter the value to search for: ");
        scanf("%s", input_value);
        if (tolower(input_value[0]) == 't' || tolower(input_value[0]) == 'y') {
            value_to_search = true;
            break;
        } else if (tolower(input_value[0]) == 'f' || tolower(input_value[0]) == 'n') {
            value_to_search = false;
            break;
        } else {
            printf("Value entered was not a boolean. Try again.");
        }
    }
    printf("\nList of records found:");
    for (i = 0; i < field->num_of_values; i++) {
        if (field->values[i] == value_to_search) {
            display_record(table_given, i);
        }
    }
}

void
search_float(struct table *table_given, int field_num) {
    struct float_field *field = table_given->floatingfields[field_num];
    int i;
    float value_to_search;
    printf("\nThe type of the selected field is interger. Enter value to search for: ");
    scanf("%f", &value_to_search);
    printf("\nMatching records: \n");
    for (i = 0; i < field->num_of_values; i++) {
        if (field->values[i] == value_to_search) {
            display_record(table_given, i);
        }
    }
}

void
search(struct table *table_given) {
    char field_to_search[32];
    int i = 0;
    printf("\nEnter the field you would like to search for: ");
    scanf("%s", &field_to_search);
    for (i = 0; i < table_given->num_str; i++) {
        if (strcmp(table_given->stringfields[i]->field_name, field_to_search) == 0) {
            search_str(table_given, i);
        }
    }
    for (i = 0; i < table_given->num_int; i++) {
        if (strcmp(table_given->intergerfields[i]->field_name, field_to_search)
            == 0) {
            search_int(table_given, i);
        }
    }
    for (i = 0; i < table_given->num_bool; i++) {
        if (strcmp(table_given->booleanfields[i]->field_name, field_to_search) == 0) {
            search_bool(table_given, i);
        }
    }
    for (i = 0; i < table_given->num_float; i++) {
        if (strcmp(table_given->floatingfields[i]->field_name, field_to_search)
            == 0) {
            search_float(table_given, i);
        }
    }
}

void
print_all(struct table *table_given) {
    int i;
    int n;
    for (i = 0; i < table_given->num_of_records; i++) {
        display_record(table_given, i);
    }
}
