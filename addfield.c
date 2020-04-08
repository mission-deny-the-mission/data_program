#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function to add field of type string
struct str_field *create_str(int num_of_records) {
    // create field variable
    struct str_field *new_field;
    // allocate memory to the new field
    new_field = malloc(sizeof(struct str_field));
    // allocate memory to values array in field
    new_field->values = malloc(sizeof(char) * num_of_records * 128);
    // get and set name for the new field
    printf("Enter the name of the new field: ");
    scanf("%s", new_field->field_name);
    // for every record
    for (new_field->num_of_values = 0;
         new_field->num_of_values < num_of_records; new_field->num_of_values++) {
        // ask user to enter new value and set it into the new field
        printf
                ("Enter new value for field %s of record %d which is type string: ",
                 new_field->field_name, new_field->num_of_values);
        scanf("%s", new_field->values[new_field->num_of_values]);
    }
    // return new field variable for integration into table
    return new_field;
}

// function to create field of type interger
struct int_field *create_int(int num_of_records) {
    // create new field variable
    struct int_field *new_field;
    // variable to hold value before it is assigned to the values array
    int value;
    // allocate memory to the new field
    new_field = malloc(sizeof(struct int_field));
    // allocate memory to the values array of the field
    char c;
    new_field->values = malloc(sizeof(int) * num_of_records);
    while (true) {
        // get and set the name of the new field from the user
        printf("Enter the name of the new field: ");
        if (scanf("%s", new_field->field_name) == 1) {
            break;
        } else {
            printf("You did not enter an interger, try again!\n");
        }
        while ((c = getchar()) != '\n' && c != EOF);
    }
    // for every existing record
    for (new_field->num_of_values = 0;
         new_field->num_of_values < num_of_records; new_field->num_of_values++) {
        // get and set the new value into the value array of the field
        printf
                ("Enter new value for field %s of record %d which is type interger: ",
                 new_field->field_name, new_field->num_of_values);
        scanf("%d", &new_field->values[new_field->num_of_values]);
    }
    // return field variable to calling function
    return new_field;
}

// function to create field of type boolean
struct bool_field *create_bool(int num_of_records) {
    // create field variable
    struct bool_field *new_field;
    // create and initialize variable to hold raw user input
    char value_input[8] = "\000\000\000\000\000\000\000\000";
    // allocate memory to new field variable
    new_field = malloc(sizeof(struct bool_field));
    // allocate memory to values array within the field
    new_field->values = malloc(sizeof(bool) * num_of_records);
    // get and set the name of the field
    printf("Enter the name of the new field: ");
    scanf("%s", new_field->field_name);
    // for every record
    for (new_field->num_of_values = 0;
         new_field->num_of_values < num_of_records; new_field->num_of_values++) {
        // while loop for verification perposes
        while (true) {
            // get value from user
            printf
                    ("Enter new value for field %s of record %d which is type boolean: ",
                     new_field->field_name, new_field->num_of_values);
            scanf("%s", &value_input);
            // if statment to detrmine if the value from the user is true
            // or false
            if (tolower(value_input[0]) == 'y' || tolower(value_input[0]) == 't') {
                new_field->values[new_field->num_of_values] = true;
                break;
            } else if (tolower(value_input[0]) == 'n' || tolower(value_input[0]) == 'f') {
                new_field->values[new_field->num_of_values] = false;
                break;
            } else {
                // if the user entered an invalid value tell them
                printf("\nYou did not enter a boolean. Try again.\n");
            }
        }

    }
    // return the new field to the calling function
    return new_field;
}

// function to create a field of type floating point
struct float_field *create_float(int num_of_records) {
    // create variable to hold new field
    struct float_field *new_field;
    char c;
    // allocate memory to the new field
    new_field = malloc(sizeof(struct float_field));
    // allocate memory to the values array inside the field
    new_field->values = malloc(sizeof(float) * num_of_records);
    // get and set the name of the field from the user
    printf("Enter the name of the new field: ");
    scanf("%s", new_field->field_name);
    // for every record
    for (new_field->num_of_values = 0;
         new_field->num_of_values < num_of_records; new_field->num_of_values++) {
        // get and set the value from the user
        while (true) {
            printf
                    ("Enter new value for field %s of record %d which is type float: ",
                     new_field->field_name, new_field->num_of_values);
            if (scanf("%f", &new_field->values[new_field->num_of_values]) == 1) {
                break;
            } else {
                printf("You did not enter a number, try again!\n");
            }
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    // return the new field to the calling function
    return new_field;
}

// function to create a new field
void *add_field(struct table *table_given) {
    // variable to hold the number of the field type required
    int field_type_input;
    // present user with the list of field types
    printf("List of field types:\n");
    printf("1. String\n");
    printf("2. Interger\n");
    printf("3. Boolean\n");
    printf("4. Floating point number\n");
    printf("Enter the type of field you would like to create: ");
    // get the field type number from the user
    scanf("%d", &field_type_input);
    // switch to determine field type and create the correct field
    // since they all work the same I only commented the first one
    switch (field_type_input) {
        case 1:
            // increment number of string fields in table
            table_given->num_str++;
            // allocate more memory the the array of field
            table_given->stringfields = realloc(table_given->stringfields,
                                                sizeof(struct str_field) * table_given->num_str);
            // create new field using function defind earlier
            table_given->stringfields[table_given->num_str - 1] = create_str(table_given->num_of_records);
            break;
        case 2:
            table_given->num_int++;
            table_given->intergerfields =
                    realloc(table_given->intergerfields, sizeof(struct int_field) * table_given->num_int);
            table_given->intergerfields[table_given->num_int - 1] =
                    create_int(table_given->num_of_records);
            break;
        case 3:
            table_given->num_bool++;
            table_given->booleanfields =
                    realloc(table_given->booleanfields, sizeof(struct bool_field) * table_given->num_bool);
            table_given->booleanfields[table_given->num_bool - 1] =
                    create_bool(table_given->num_of_records);
            break;
        case 4:
            table_given->num_float++;
            table_given->floatingfields =
                    realloc(table_given->floatingfields, sizeof(struct float_field) * table_given->num_float);
            table_given->floatingfields[table_given->num_float - 1] =
                    create_float(table_given->num_of_records);
            break;
        default:
            // tell the user they entered the wrong input
            printf("You entered an invalid type. Cancelling operation.");
            break;
    }
}
