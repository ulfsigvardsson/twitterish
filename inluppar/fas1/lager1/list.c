#include <stdlib.h>
#include "list.h"
#include "db.h"

struct link {
  L elem;
  link_t *next; // Sista elementets next ska vara NULL.
};

struct list {
  link_t *first;
  link_t *last; 
};

list_t *list_new() {
  list_t *new = calloc(1, sizeof(list_t));
  return new;
}

void list_prepend(list_t *list, L elem) {
  link_t *current_first = list->first;
  link_t *new_first = calloc(1, sizeof(link_t));
  new_first->elem   = elem;

  if (current_first) {
    new_first->next   = current_first; 
    list->first = new_first;
  }
  else {
    list->first = new_first; // Detta kodstycke kan vi bryta ut, återanvänds...
    list->last = new_first;
  }
}

void list_append(list_t *list, L elem) {
  link_t *current_last = list->last;
  link_t *new_last = calloc(1, sizeof(link_t));
  new_last->elem  = elem;
  
  if (current_last) {
    current_last->next  = new_last;
    list->last = new_last;
  }
  else {
    list->first = new_last;
    list->last = new_last;
  } 
}

int list_length(list_t *list) {
  int count = 0;
  if (list->first) {
     while (list->first[count].next) {
         ++count;
     }
  }
  return count;
}
  

bool list_remove(list_t *list, int index, L *elem) {
  if ( index < list_length(list) && index >= 0) {
     *elem = list->first[index].elem;
     ++(list->first[index-1].next);
     return true;
  }
  else
    { return false; }  // felaktigt index, finns ej i listan.
}

L list_get(list_t *list, int index) {
  L val = list->first[index].elem;
  return val;
}

L list_first(list_t *list) {
  L first = list->first->elem;
  return first;  
}

L list_last(list_t *list) {
  L last = list->last->elem;
  return last;
}
