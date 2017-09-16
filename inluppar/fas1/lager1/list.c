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

// Allokerar en ny link_t och nitierar en tom lista med den
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
  if (list->last) {
  link_t *new_last = calloc(1, sizeof(link_t));
  new_last->elem = elem;
  list->last->next = new_last;
  list->last = new_last;
  }
  else {
    initiate_list(list, elem);
  }
}

void list_prepend(list_t *list, L elem) {
 link_t *new_first = calloc(1, sizeof(link_t));
 new_first->elem   = elem;
 new_first->next   = list->first;
 list->first       = new_first;
}

void print_list(list_t *list) {
  if (not_empty_list(list)) {
    link_t *current = list->first;
    int i =1;
    while (current !=NULL) {
      printf("Värde plats %d: %d\n", i, current->elem);
      current = current->next;
      ++i;
    } 
  }
  else {
    printf("Tom lista!\n");
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

bool pop(list_t *list, L *elem) {
  if (list_length(list) == 1) { // cc för singletons
    *elem = list->first->elem;
    list->first = list->last = NULL;
    return true; 
  }
  else {
    link_t *tmp =list->first;
    *elem = tmp->elem;
    list->first = list->first->next;
    free(tmp);
    return true;
  }
}

bool list_remove(list_t *list, int index, L *elem) {
  if (!not_empty_list(list)) {
    return false;
  }
  else if (index == 0) { 
    pop(list, elem);
  }
  else {
    link_t *current = list->first;
    int i = 0;
    while (current->next != NULL && i < index-1) {
      current = current->next;
      ++i;
    }
    link_t *tmp = current->next;
    *elem = tmp->elem;
    current->next = current->next->next;
    free(tmp);
    return true;
  }
}


bool list_insert(list_t *list, int index, L elem) {
  int size = list_length(list); 
  if (index < 0) {
    index = size + 1 + index;   // Om angivet index är negativt -> gör det positivt.
  }
  if (index == 0) {
    list_prepend(list, elem);   // Vid insert på plats 1, används prepend.
  }
  if (!(0 < index && index < size)) {
    return false;              // ogiltigt index, ingen insert sker.
  }
  
  int i = 1;
  link_t *cursor = list->first;
  while (i < index) {
    cursor = cursor->next;
    ++i;
  }
  link_t *new_insert = calloc(1, sizeof(link_t));
  new_insert->elem = elem;
  new_insert->next = cursor->next;
  cursor->next = new_insert;
  return true;
}

// Inte definierad för tomma listor
L list_get(list_t *list, int index) {
  int i=0;
  link_t *cursor = list->first;
  while (cursor && i < index) {
    cursor = cursor->next;
    ++i;
  }
  return cursor->elem;
}

L list_first(list_t *list) {
  L first = list->first->elem;
  return first;  
}

L list_last(list_t *list) {
  L last = list->last->elem;
  return last;
}


void delete_list(list_t *list) {
  link_t *current = list->first;

  while (current->next) {
    link_t *temp = current;
    current = current->next;
    free(temp);
  }
  free(list);
}
