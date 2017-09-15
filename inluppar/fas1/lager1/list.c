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


bool list_remove(list_t *list, int index, L *elem) {
  if (!not_empty_list(list)) {
    return false;
  }
  else if (index == 0) { //corner case för pop, bryt ut denna till en pop();

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

void bool_list_insert(list_t *list, int index, L elem) {
  int i = 0;
  link_t *cursor = list->first;

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
