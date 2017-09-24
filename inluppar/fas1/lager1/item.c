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

item_t *item_empty() {
  item_t *item = calloc(1, sizeof(item_t));
  return item;
}

void item_set_name(item_t *item, char *name) {
  item->name = name;
}

void item_set_description(item_t *item, char *descr) {
  item->descr = descr;
}


void item_set_price(item_t *item, int price) {
  item->price = price;
}


void item_set_shelf(shelf_t *shelf, char *id) {
  shelf->id =id;
}

void item_set_amount(shelf_t *shelf, int amount) {
  shelf->amount = amount;
}

void item_set_shelves(item_t *item, list_t *shelves) {
  item->shelves = shelves;
}
char *item_name(item_t *item) {
  return item->name;
}

char *item_descr(item_t *item) {
  return item->descr;
}

int item_price(item_t *item) {
  return item->price;
}

list_t *item_shelves(item_t *item) {
  return item->shelves;
}

char *shelf_id(shelf_t *shelf) {
  return shelf->id;
}

int shelf_amount(shelf_t *shelf) {
  return shelf->amount;
}
