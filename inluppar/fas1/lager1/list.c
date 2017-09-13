#include <stdlib.h>
#include "list.h"
#include "db.h"
#include <stdio.h> // for printfunktionen, kan tas bort om den tas bort

bool not_empty_list(list_t *list);
void initiate_list(list_t *list, L  elem);

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

void initiate_list(list_t *list, L elem) {
  link_t *new =calloc(1, sizeof(link_t));
  new->elem = elem;
  list->first = new;
  list->last = new;
}

bool not_empty_list(list_t *list) {
  return list->first;
}

void list_append(list_t *list, L elem) {
  link_t *current = list->first;
  if (not_empty_list(list)) {
    while (current->next != NULL) {
      current = current->next; // Vi stegar oss fram till det sista elementet
    }
    current->next = calloc(1, sizeof(link_t));
    current->next->elem = elem;
    current->next->next = NULL;
  }
  else {
    initiate_list(list, elem);
  }
}

void list_prepend(list_t *list, L elem) {
  link_t *current_first = list->first;
  link_t *new_first = calloc(1, sizeof(link_t));
  new_first->elem   = elem;

  // Om listan inte är tom pekar vårt nya första listobjekt på det gamla första objektet
  if (not_empty_list(list)) { 
    new_first->next = current_first; 
    list->first = new_first;
  }
  // Annars är det nya elementet det enda är både första och sista elementet
  else {
    initiate_list(list, elem);
  }
}

void print_list(list_t *list) {

  link_t *current = list->first;
  int i =1;
  while (current !=NULL) {
    printf("Värde plats %d: %d\n", i, current->elem);
    current = current->next;
    ++i;
  }
}

int list_length(list_t *list) {
  int count = 0; // räknare för längden
  link_t *current = list->first;

  while (current !=NULL) {
    ++count;
    current = current->next;
  }
  return count;
}


bool list_remove(list_t *list, int index, L *elem) {
  if (not_empty_list) {
    int i = 0;
    int retval;
    link_t *current = list->first;

    for (int i = 0; i < index-1; ++i) {
      if (current->next == NULL) {
        return false;
      }
      current = current->next;
    }
    link_t *temp = current->next;
    retval = temp->elem;
    current->next = temp->next;
    free(temp);
    return true;
  }
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
