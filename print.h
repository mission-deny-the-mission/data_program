#ifndef print
#define print

void print_all(struct table *table_given);

void search(struct table *table_given);

void search_int(struct table *table_given, int num_of_field);

void search_str(struct table *table_given, int num_of_field);

void search_bool(struct table *table_given, int num_of_field);

void search_float(struct table *table_given, int num_of_field);

void display_record(struct table *table_given, int num_of_record);

#endif // print
