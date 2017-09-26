#include <stdlib.h>
#include "list.h"


bool not_empty_list(list_t *list);
void initiate_list(list_t *list, L  elem);

struct link
{
  L elem;
  link_t *next; // Sista elementets next ska vara NULL.
};

struct list
{
  link_t *first;
  link_t *last; 
};

list_t *list_new()
{
  list_t *new = calloc(1, sizeof(list_t));
  return new;
}

// Allokerar en ny link_t och nitierar en tom lista med den
void initiate_list(list_t *list, L elem)
{
  link_t *new =calloc(1, sizeof(link_t));
  new->elem = elem;
  list->first = new;
  list->last = new;
}

bool not_empty_list(list_t *list)
{
  return list->first;
}

void list_append(list_t *list, L elem)
{
  if (list->last)
  {
    link_t *new_last = calloc(1, sizeof(link_t));
    new_last->elem = elem;
    list->last->next = new_last;
    list->last = new_last;
  }
  else {
    initiate_list(list, elem);
  }
}

void list_prepend(list_t *list, L elem)
{
  if (list->first)
    {
     link_t *new_first = calloc(1, sizeof(link_t));
     new_first->elem   = elem;
     new_first->next   = list->first;
     list->first       = new_first;
    }
  else {
    initiate_list(list, elem);
  }
}
                         //   ***  VISA PÅ LABBEN !!!   ***

int list_length(list_t *list)
{
  int count = 0; // räknare för längden
  link_t *current = list->first;

  while (current !=NULL)
  {
    ++count;
    current = current->next;
  }
  return count;
}

int list_length_rec_aux(link_t *link)
{
  if (!link) {
    return 0;
  }
  else
  {
    return ( 1 + list_length_rec_aux(link->next)); 
  }
}

int list_length_rec(list_t *list)
{
  link_t *link = list->first;
  return list_length_rec_aux(link); 
}


int list_length_tailrec_aux(link_t *link, int acc)
{
  if (!link)
  {
    return acc;
  }
  else
  {
    return list_length_tailrec_aux(link->next, acc+1);
  }
}

int list_length_tailrec(list_t *list)
{
  link_t *link = list->first;
  return list_length_tailrec_aux(link, 0);
}

                               //   ***  VISA PÅ LABBEN !!!   ***


bool pop(list_t *list, L *elem)
{
  if (list_length(list) == 1)
  { // cc för singletons
    *elem = list->first->elem;
    list->first = list->last = NULL;
    return true; 
  }
  else
  {
    link_t *tmp =list->first;
    *elem = tmp->elem;
    list->first = list->first->next;
    free(tmp);
    return true;
  }
}

bool list_remove(list_t *list, int index, L *elem)
{
  if (!not_empty_list(list))
  {
    return false;
  }
  else if ( index < 0 || list_length(list) < index)
  {
    return false;              // ogiltigt index, ingen insert sker.
  }
  else
  {
    if (index == 0)
    { 
    return pop(list, elem);
    }
    else
    {
    link_t *current = list->first;
    int i = 0;
    
    while (current->next != NULL && i < index-1) { //TODO: support för index som inte finns

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
}


bool list_insert(list_t *list, int index, L elem)
{
  int size = list_length(list); 
  if (index < 0)
  {
    index = size + 1 + index;   // Om angivet index är negativt -> gör det positivt.
  }
  if ( index < 0 || size < index)
  {
    return false;              // ogiltigt index, ingen insert sker.
  }
  if (index == 0)
  {
    list_prepend(list, elem);
    return true;                // Vid insert på plats 1, används prepend.
  }
  else
  {
    int i = 1;
    link_t *cursor = list->first;
    while (i < index)
      {
        cursor = cursor->next;
        ++i;
      }
  link_t *new_insert = calloc(1, sizeof(link_t));
  new_insert->elem = elem;
  new_insert->next = cursor->next;
  cursor->next = new_insert;
  return true;
  }
}

// Inte definierad för tomma listor
L *list_get(list_t *list, int index)
{
  int i=0;
  link_t *cursor = list->first;
  while (cursor && i < index)
  {
    cursor = cursor->next;
    ++i;
  }
  return &cursor->elem;
}

L *list_first(list_t *list)
{
  return &list->first->elem;
}

L *list_last(list_t *list)
{
  return &list->last->elem;
}


/// Deletes a list. 
///
/// \param list pointer to the list
/// \param cleanup a function that takes an element as
///        argument, to be used to free memory. If this param is 
///        NULL, no cleanup of keys or elements will happen.
void list_delete(list_t *list, list_action cleanup)
{
  link_t *tmp;
  link_t *current = list->first;
  while (current)
  {
    tmp = current;
    current = current->next;
    if (cleanup)
      {
        cleanup(tmp->elem); // cleanup definieras inte här
        free(tmp); 
    }
    else
    {
      free(tmp); 
    }
  }
}

/// Applies a function to all elements in a list in list order
///
/// \param list the list
/// \param fun the function to apply to all elements
/// \param data an extra argument passed to each call to fun (may be NULL)
void list_apply(list_t *list, list_action2 func, void *data)
{
  if (!list)
  {
    return;
  }
  else
  {
    link_t *current = list->first;
    while (current)
    {
      func(current->elem, data);
      current = current->next;
    }
  }
}
