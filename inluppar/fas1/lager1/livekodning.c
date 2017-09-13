#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


typedef struct list list_t;
typedef struct link link_t;
typedef struct iter iter_t;

struct iter {
  link_t *current;
};

struct list {
  link_t *first;
  link_t *last;
};

struct link {
  char *value;
  link_t *next;
};

list_t *list_new();
void list_delete(list_t *list);
void list_prepend(list_t *list, char *value);
char *list_get(list_t *list, int index);
link_t *link_new(char *value, link_t *next);
iter_t list_iterator(list_t *list);
char *iter_next(iter_t *iter);
bool iter_has_more(iter_t *iter);

int main(int argc, char *argv[]) {
  list_t *list = list_new();

  for (int i =0 ;i < argc; ++i) {
    list_prepend(list, argv[i]);
  }

  iter_t *iter =list_iterator(list);
  while (iter_has_more(&iter)) {
    //do work
  }
  return 0;
}


list_t *list_new() {
  return calloc(1, sizeof(struct list));
}
void list_delete(list_t *list) {
  link_t *cursor = list->first;

  while (cursor) {
    link_t *temp = cursor;
    cursor = cursor->next;
    free(temp); 
  }
  free(list);
}
void list_prepend(list_t *list, char *value) {
  list->first = link_new(value, list->first);
  if (list->last == NULL) {
    list->last = list->first;    
  }
}

char *list_get(list_t *list, int index) {
  link_t *cursor = list->first;

  for (int i = 0; cursor && i < index; ++i) {
    cursor = cursor->next;
  }
  return cursor ? cursor->value : NULL;
}

link_t *link_new(char *value, link_t *next) {
  link_t *result = malloc(sizeof(struct link));

  if (result) {
    result->next = value;
    result->value = value;
  }
  return result;
}

iter_t list_iterator(list_t *list) {
  iter_t result;
  result.current = list->first;
  return result;
}

void iter_delete(iter_t *iter) {
  free(iter);
}
char *iter_next(iter_t *iter) {
  if (iter_has_more(iter)) {
    char *result = iter->current->value;
    iter->current = iter->current->next;
    return result; 
  }
  else {
    return NULL;
  }
}
bool iter_has_more(iter_t *iter) {
  return iter->current != NULL;
}
