#include <stdlib.h>
#include <string.h>
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

shelf_t *shelf_empty()
{
  shelf_t *s = calloc(1, sizeof(shelf_t));
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
  item->shelves = list_new();
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

//FIXME: måste kopiera lsitan av hyllor, annars har de samma pekare, samma med beskrivningen
void item_copy(item_t *original, item_t *copy) {
  copy->name = strdup(original->name);
  copy->descr = strdup(original->descr);
  copy->price = original->price;
  shelf_copy(original, copy);
}

void shelf_copy(item_t *original, item_t *copy)
{
  list_t *to = copy->shelves;
  list_t *from = original->shelves;
  int length = list_length(original->shelves);
  list_t *temp_list = list_new();
  
  for (int i = 0; i < length; ++i)
  {
    L *tmp = list_get(from, i);
    int amount = shelf_amount(*tmp);
    char *id = strdup(shelf_id(*tmp));
    shelf_t *new = shelf_new(id, amount);
    list_append(temp_list, new);
  }

  copy->shelves = temp_list;
  free(to); // Måste ihn och gröta djupare än såhär
}
