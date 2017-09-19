#ifndef ITEM_H
#define ITEM_H
#include "list.h" // Cykelberoende, list.h är beroende av item.h!!

typedef struct item item_t;
typedef struct shelf shelf_t;

item_t *item_new(char *name, char *descr, int price, char *shelf_id, int amount);

#endif
