#include <stdlib.h>
#include <string.h>
#include "item.h"



struct item {
  char *name;
  char *descr;
  int price;
  elem_t *shelves;
};

struct shelf {
  char *id;
  int amount;
};

typedef struct shelf shelf_t;

shelf_t *shelf_new(char *id, int amount)
{ 
  return NULL;
}


item_t *item_new(char *name, char *descr, int price)
{
  return NULL;
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

void item_set_shelves(item_t *item, elem_t *shelves) {
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

elem_t *item_shelves(item_t *item) {
  return item->shelves;
}

char *shelf_id(shelf_t *shelf) {
  return shelf->id;
}

int shelf_amount(shelf_t *shelf) {
  return shelf->amount;
}

void item_copy(item_t *original, item_t *copy) {
  copy->name = strdup(original->name);
  copy->descr = strdup(original->descr);
  copy->price = original->price;
  shelf_copy(original, copy);
}

void shelf_copy(elem_t *original, elem_t *copy)
{
  return;
}
