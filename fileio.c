#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// function to strip the whitespace from a character
// this was probably a code snippet from the internet and
// I do not know how this works so it will not be commented
void strip(char *s) {
    char *p2 = s;
    while (*s != '\0') {
        if (*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

// function to save a table to a file
void save(struct table *table_given) {
    // string to hold the name of the file required to save to
    char filename[128];
    // holds the opened file
    FILE *filep;
    // holds the current line beign read from the file
    char line[128];
    // incrementor variables
    int i;
    int n;
    // asks the user where they would like to save the file
    printf("Enter the filename to save to: ");
    scanf("%s", filename);
    // opens the file and places the io stream in the filep variable created earlier
    filep = fopen(filename, "w");
    // this section writes the database accounting infomation to the file
    // this includes the total nummber of records and the number of different types of field
    sprintf (line, "%d", table_given->num_str);
    fprintf(filep, line);
    fprintf(filep, "\n");
    sprintf (line, "%d", table_given->num_int);
    fprintf(filep, line);
    fprintf(filep, "\n");
    sprintf (line, "%d", table_given->num_bool);
    fprintf(filep, line);
    fprintf(filep, "\n");
    sprintf (line, "%d", table_given->num_float);
    fprintf(filep, line);
    fprintf(filep, "\n");
    sprintf (line, "%d", table_given->num_of_records);
    fprintf(filep, line);
    fprintf(filep, "\n");
    // this for loop is responsible for writing all the fields of type string to the file
    for (i = 0; i < table_given->num_str; i++) {
        // write the name of the field to the file
        fprintf(filep, table_given->stringfields[i]->field_name);
        fprintf(filep, "\n");
        // for every record in the table
        for (n = 0; n < table_given->num_of_records; n++) {
            // print out the value of the record for the current field
            fprintf(filep, table_given->stringfields[i]->values[n]);
            fprintf(filep, "\n");
        }
    }
    // this loop is responsible for writing all the fields of type interger to the file
    for (i = 0; i < table_given->num_int; i++) {
        // write the name of the filed to the file
        fprintf(filep, table_given->intergerfields[i]->field_name);
        fprintf(filep, "\n");
        // for every record in the table
        for (n = 0; n < table_given->num_of_records; n++) {
            // convert the current value to a string
            sprintf (line, "%d", table_given->intergerfields[i]->values[n]);
            // write the value to the file
            fprintf(filep, line);
            fprintf(filep, "\n");
        }
    }
    // this for loop writes each field of type boolean to the file
    for (i = 0; i < table_given->num_bool; i++) {
        // write the name of the field to the file
        fprintf(filep, table_given->booleanfields[i]->field_name);
        fprintf(filep, "\n");
        // for every record in the file
        for (n = 0; n < table_given->num_of_records; n++) {
            // convert the current value to type string
            sprintf (line, "%d", table_given->booleanfields[i]->values[n]);
            // write out the value to the file
            fprintf(filep, line);
            fprintf(filep, "\n");
        }
    }
    // this for loop is responsible for writing all the fields of type
    // floating point to the file
    for (i = 0; i < table_given->num_float; i++) {
        // write the name of the field to the file
        fprintf(filep, table_given->floatingfields[i]->field_name);
        fprintf(filep, "\n");
        // for every record in the table
        for (n = 0; n < table_given->num_of_records; n++) {
            // convert the value into a string
            sprintf (line, "%f", table_given->floatingfields[i]->values[n]);
            // write the value to the file
            fprintf(filep, line);
            fprintf(filep, "\n");
        }
    }
    // close the file once finished opening it
    fclose(filep);
}

// function to open a file as the current table
struct table *open() {
    // variable to store filename
    char filename[128];
    // variable to store the table beign generated
    struct table *new_table;
    // variable to contain the file object
    FILE *filep;
    // incrementor variables
    int i;
    int n;
    // variables to store the lines which are beign read from a file
    char line[128];
    char linel[32];
    // ask the user for the name of the file they would like to open
    printf("Enter the filename you want to open: ");
    scanf("%s", filename);
    // open the file for reading
    filep = fopen(filename, "r");
    // allocate memory for the new table beign generated
    new_table = malloc(sizeof(struct table));
    // this section of the program gets the table accounting information
    // this includes the number of fields of each type and the number of records
    fgets(line, 128, filep);
    new_table->num_str = atoi(line);
    fgets(line, 128, filep);
    new_table->num_int = atoi(line);
    fgets(line, 128, filep);
    new_table->num_bool = atoi(line);
    fgets(line, 128, filep);
    new_table->num_float = atoi(line);
    fgets(line, 128, filep);
    new_table->num_of_records = atoi(line);
    // this section of code is responsibe for reading and creating the fields of type string
    // the first line alloates memory to the array of fields of type string
    // this is an array of pointers which is itself dyanmically allocated
    new_table->stringfields = malloc(sizeof(struct str_field *) * new_table->num_str);
    // for every field of type string
    for (i = 0; i < new_table->num_str; i++) {
        // allocate memory to the new field
        new_table->stringfields[i] = malloc(sizeof(struct str_field));
        // read the name of the field from the file
        fgets(linel, 32, filep);
        strip(linel);
        // copy the name read fron the file to the new field
        strcpy (new_table->stringfields[i]->field_name, linel);
        // allocate memory to the value array inside the new field
        new_table->stringfields[i]->values = malloc(sizeof(char) * 128 * new_table->num_of_records);
        // set the number of records as the number of values in the new field
        new_table->stringfields[i]->num_of_values = new_table->num_of_records;
        // for every value in the new field
        for (n = 0; n < new_table->num_of_records; n++) {
            // read the value from the file
            fgets(line, 128, filep);
            strip(line);
            // copy the new value into the value array
            strcpy (new_table->stringfields[i]->values[n], line);
        }
    }
    // this section performs the same job as the above section but for fields of type interger
    // the code works the same as above except with  different variable names and
    // it converts the values type from string to interger
    new_table->intergerfields = malloc(sizeof(struct int_field *) * new_table->num_int);
    for (i = 0; i < new_table->num_int; i++) {
        new_table->intergerfields[i] = malloc(sizeof(struct int_field));
        fgets(linel, 32, filep);
        strip(linel);
        strcpy (new_table->intergerfields[i]->field_name, linel);
        new_table->intergerfields[i]->values = malloc(sizeof(int) * new_table->num_of_records);
        new_table->intergerfields[i]->num_of_values = new_table->num_of_records;
        for (n = 0; n < new_table->num_of_records; n++) {
            fgets(line, 128, filep);
            new_table->intergerfields[i]->values[n] = atoi(line);
        }
    }
    // this section does the same for fields of type boolean
    new_table->booleanfields = malloc(sizeof(struct bool_field *) * new_table->num_bool);
    for (i = 0; i < new_table->num_bool; i++) {
        new_table->booleanfields[i] = malloc(sizeof(struct bool_field));
        fgets(linel, 32, filep);
        strip(linel);
        strcpy (new_table->booleanfields[i]->field_name, linel);
        new_table->booleanfields[i]->values = malloc(sizeof(bool) * new_table->num_of_records);
        new_table->booleanfields[i]->num_of_values = new_table->num_of_records;
        for (n = 0; n < new_table->num_of_records; n++) {
            fgets(line, 128, filep);
            new_table->booleanfields[i]->values[n] = atoi(line);
        }
    }
    // this section does the same except for fields of type floating point
    new_table->floatingfields = malloc(sizeof(struct float_field *) * new_table->num_of_records);
    for (i = 0; i < new_table->num_float; i++) {
        new_table->floatingfields[i] = malloc(sizeof(struct float_field));
        fgets(linel, 32, filep);
        strip(linel);
        strcpy (new_table->floatingfields[i]->field_name, linel);
        new_table->floatingfields[i]->values = malloc(sizeof(float) * new_table->num_of_records);
        new_table->floatingfields[i]->num_of_values = new_table->num_of_records;
        for (n = 0; n < new_table->num_of_records; n++) {
            fgets(line, 128, filep);
            new_table->floatingfields[i]->values[n] = atof(line);
        }
    }
    // close the file that was opened earlier
    fclose(filep);
    // return the newly opened table to the main function
    return new_table;
}

// this function is used to delete a table and clear its information
void clear_table(struct table *table_given) {
    // incrementor variable
    int i;
    // for every field of type string
    for (i = 0; i < table_given->num_str; i++) {
        // de allocate the memory for the values
        free(table_given->stringfields[i]->values);
        // deallocate the memory for the fields structure
        free(table_given->stringfields[i]);
    }
    // for every field of type intereger
    for (i = 0; i < table_given->num_int; i++) {
        // deallocate the values in the field
        free(table_given->intergerfields[i]->values);
        // deallocaate the field structure
        free(table_given->intergerfields[i]);
    }
    // for every field of type boolean
    for (i = 0; i < table_given->num_bool; i++) {
        // deallocate the values
        free(table_given->booleanfields[i]->values);
        // deallocate the fields structure
        free(table_given->booleanfields[i]);
    }
    // for every field of type floating point
    for (i = 0; i < table_given->num_float; i++) {
        // deallocate the values
        free(table_given->floatingfields[i]->values);
        // deallocate the fields structure
        free(table_given->floatingfields[i]);
    }
    // deallocate the pointer aray of fields
    if (table_given->num_str != 0) {
        free(table_given->stringfields);
    }
    if (table_given->num_int != 0) {
        free(table_given->intergerfields);
    }
    if (table_given->num_bool != 0) {
        free(table_given->booleanfields);
    }
    if (table_given->num_float != 0) {
        free(table_given->floatingfields);
    }
    // deallocate the tables structure
    free(table_given);
}
