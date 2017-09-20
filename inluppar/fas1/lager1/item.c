#include <stdlib.h>
#include "item.h"



struct item {
  char *name;
  char *descr;
  int price;
  list_t *shelves;
};

struct shelf {
  char *id;
  int amount;
};

typedef struct shelf shelf_t;

shelf_t *shelf_new(char *id, int amount) { 
  shelf_t *s = calloc(1, sizeof(shelf_t));
  s->id = id;
  s->amount = amount;
  return s;
}

item_t *item_new(char *name, char *descr, int price, char *shelf_id, int amount) {
  item_t *item = calloc(1, sizeof(item_t));
  item->name   = name;
  item->descr  = descr;
  item->price  = price;
  shelf_t *new_shelf = shelf_new(shelf_id, amount);
  item->shelves= list_new();
  list_append(item->shelves, new_shelf);
  return item;
}

