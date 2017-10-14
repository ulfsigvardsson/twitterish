#include <stdlib.h>
#include <string.h>
#include "item.h"
#include <assert.h>


struct item {
  char *name;
  char *descr;
  int price;
  list_t *shelves;
};
//! \struct En struct för hyllor
/*!
 *
 */
struct shelf
{
  char *id; /*!< Hyllans namn*/
  int amount; /*!< Antal varor lagrade på hyllan*/
};

shelf_t *shelf_new(char *id, int amount)
{ 
  shelf_t *s = calloc(1, sizeof(shelf_t));
  assert(s);
  s->id = id;
  s->amount = amount;
  return s;
}

shelf_t *shelf_empty()
{
  shelf_t *s = calloc(1, sizeof(shelf_t));
  return s;
}

item_t *item_new(char *name, char *descr, int price) {
  item_t *item = calloc(1, sizeof(item_t));
  assert(item);
  
  item->name   = name;
  item->descr  = descr;
  item->price  = price;
  
  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);

  item->shelves = shelves;
  return item;
}

void item_add_shelf(item_t *item, elem_t shelf)
{
  list_append(item->shelves, shelf);
}

void item_set_name(item_t *item, char *name)
{
  if (item) item->name = name;

}

void item_set_description(item_t *item, char *descr)
{
  if (item)
    {
      //char* tmp = item->descr;
      item->descr = descr;
      //free(tmp);
      //Dessa rader free:ar en del av item strukten, vilket kraschar skit
    }
}


void item_set_price(item_t *item, int price)
{
  if (item) item->price = price;
}


void item_set_shelf(shelf_t *shelf, char *id)
{
  if (shelf) shelf->id =id;    
}


void item_set_shelves(item_t *item, list_t *shelves)
{
  item->shelves = shelves;
}

char *item_name(item_t *item)
{
  return item->name;
}

char *item_descr(item_t *item)
{
  return item->descr;
}

int item_price(item_t *item)
{
  return item->price;
}

list_t *item_shelves(item_t *item)
{
  if (item) return item->shelves; 
  return NULL;
}

char *shelf_id(shelf_t *shelf)
{
  if (shelf) return shelf->id;
  return NULL;
}

void set_shelf_id(shelf_t *shelf, char *id)
{
  shelf->id = id;
}

int shelf_amount(shelf_t *shelf) {
  return shelf->amount;
}

void shelf_set_amount(shelf_t *shelf, int amount)
{
  shelf->amount = amount;
}
void shelf_add_amount(shelf_t *shelf, int amount)
{
  if (shelf)
    {
      int current = shelf->amount;
      shelf->amount = current+amount;  
    }
  
}
int shelf_compare(elem_t elem1, elem_t elem2)
{
  shelf_t *a = (shelf_t*)elem1.p;
  shelf_t *b = (shelf_t*)elem2.p;

  if (a && b) return strcmp(a->id, b->id);
  return -1;
  // kanske lägga till att inputvärdet automatiskt är större än NULL för att få ett vettigt returnvärde
}

int item_compare(elem_t key1, elem_t key2)
{
  char* k1 = (char*)key1.p;
  char* k2 = (char*)key2.p;

  if (k1 && k2 ) return strcmp(k1, k2); 
  // kanske lägga till att inputvärdet automatiskt är större än NULL för att få ett vettigt returnvärde
  return -1000;
}

void item_free(elem_t elem)
{
  item_t *item = elem.p;

  if (item)
    {
      if (item->name) free(item->name);
      item->name=NULL;
      if (item->descr) free(item->descr);
      item->descr = NULL;
      list_delete(item->shelves, true);
      free(item);
    }
}

void shelf_free_aux(shelf_t *shelf)
{
  if (shelf)
    {
      free(shelf->id);
      free(shelf);
    }
}

void key_free(elem_t elem)
{
  char *key = elem.p;
  free(key);
}

void shelf_free(elem_t elem)
{
  shelf_t *shelf = (shelf_t*)elem.p;
  if (shelf) shelf_free_aux(shelf);    
}

elem_t shelf_copy(elem_t shelf)
{
  return shelf; 
}

//FIXME: vi kan nog ta bort allt utom ifsatsen
elem_t item_copy(elem_t item)
{
  return item;
}


elem_t shelf_deep_copy(elem_t shelf)
{
  shelf_t *copy     = calloc(1, sizeof(shelf_t));
  shelf_t *original = (shelf_t*)shelf.p;
  
  copy->id = strdup(original->id);
  copy->amount = original->amount;
  
  elem_t result = { .p = copy };
  return result;
}

item_t *item_deep_copy(elem_t elem)
{
  item_t *to = calloc(1, sizeof(item_t));
  item_t *from = elem.p;
  to->name  = strdup(from->name);
  to->descr = strdup(from->descr);
  to->price = from->price;

  list_t *shelves_copy = list_new(shelf_copy, shelf_free, shelf_compare); 
  elem_t tmp;
  int i = 0;
  
  while (list_get(from->shelves, i, &tmp))
     {
       elem_t shelf = shelf_deep_copy(tmp);
       list_append(shelves_copy, shelf);
       ++i;
     }
  
  to->shelves = shelves_copy;
  return to;
 }
