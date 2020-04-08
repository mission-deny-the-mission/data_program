#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "addfield.h"
#include "print.h"
#include "addrecord.h"
#include "deleterecord.h"
#include "editrecord.h"
#include "deletefield.h"
#include "fileio.h"

// a function to create and initialize a new table
struct table *newtable() {
    // create the table and allocate memory to it
    struct table *ntable = malloc(sizeof(struct table));
    // initlize the numbers of fields to 0
    ntable->num_str = 0;
    ntable->num_int = 0;
    ntable->num_bool = 0;
    ntable->num_float = 0;
    // initialize the number of records to 0
    ntable->num_of_records = 0;
    // return the new table to the calling function
    return ntable;
}

int main() {
    // create dynamicaly allocated table
    struct table *current_table;
    // create variable to hold the number of the current function
    int function = 0;
    // used for asking the user if they are sure about something
    char verification[8];
    char c;
    // initialize the new table
    current_table = newtable();
    // while the user choses to continue the programs execution
    while (true) {
        // print out program options
        printf("\nList of program functions:\n");
        printf("1. Add a new field\n");
        printf("2. Add a new record\n");
        printf("3. Edit an exisiting record\n");
        printf("4. Delete an eixsitng record\n");
        printf("5. Delete a field\n");
        printf("6. Print all data\n");
        printf("7. Search for data\n");
        printf("8. Save to a file\n");
        printf("9. Open a file\n");
        printf("10. New database\n");
        printf("11. Quit\n");
        // get the function number the user desires
        while (true) {
            // ask the user for the number of the function they would like to perform
            printf("Enter the function you would like to perform: ");
            // use if stement to get the input from the user and determine
            // if is is correct
            if (scanf("%d", &function) == 1) {
                // break out of the while loop if the user entered a number
                break;
            } else {
                // if the user did not enter a number tell them of their mistake
                printf("You did not enter an interger, try again!\n");
            }
            // clear the input buffer
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // find the function the user desires from the list and
        // trigger the aproperiate action
        switch (function) {
            case 1:
                add_field(current_table);
                break;
            case 2:
                add_record(current_table);
                break;
            case 3:
                edit_record(current_table);
                break;
            case 4:
                delete_record(current_table);
                break;
            case 5:
                delete_field(current_table);
                break;
            case 6:
                print_all(current_table);
                break;
            case 7:
                search(current_table);
                break;
            case 8:
                save(current_table);
                break;
            case 9:
                clear_table(current_table);
                current_table = open();
                break;
            case 10:
                // ask the user if they are sure they would like to clear the table
                printf("Are you sure you want to delete this table? ");
                // get the users anwser
                scanf("%s", &verification);
                // if the user anwsered yes
                if (tolower(verification[0]) == 'y') {
                    // clear the current table
                    clear_table(current_table);
                    // create and initialize a new table
                    current_table = newtable();
                }
                    // if the user chose not to wipe the table display a message
                else {
                    printf("Cancelling operation.");
                }
                break;
            case 11:
                // ask the user if they are sure they would like to quit
                printf("Are you sure you want to quit? ");
                // get the users anwser
                scanf("%s", &verification);
                // if the user did not decide to quit
                if (tolower(verification[0]) != 'y') {
                    // set the function number to 0
                    function = 0;
                }
                    // if the user did dicide to quit
                else {
                    // deallocate the current table
                    clear_table(current_table);
                }
                break;
                // if user entered invalid function number
            default:
                // tell them
                printf("Invalid function number entered.\n");
                break;
        }
        // if the function number is 11
        if (function == 11) {
            // break out of the main loop
            break;
        }
    }
    return 0;
}
