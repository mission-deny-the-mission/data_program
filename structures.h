#ifndef strucutres
#define strucutres
typedef int bool;
#define true 1
#define false 0
struct str_field {
    char (*values)[128];
    char field_name[32];
    int num_of_values;
};
struct int_field {
    int *values;
    char field_name[32];
    int num_of_values;
};
struct bool_field {
    bool *values;
    char field_name[32];
    int num_of_values;
};
struct float_field {
    float *values;
    char field_name[32];
    int num_of_values;
};
struct table {
    struct str_field **stringfields;
    struct int_field **intergerfields;
    struct bool_field **booleanfields;
    struct float_field **floatingfields;
    int num_str;
    int num_int;
    int num_bool;
    int num_float;
    int num_of_records;
};
#endif // strucutres
