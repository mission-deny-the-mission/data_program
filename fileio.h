#ifndef fileio
#define fileio

void save(struct table *table_given);

struct table *open();

void clear_table(struct table *table_given);

#endif
