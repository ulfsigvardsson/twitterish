#include "list.h"

typedef struct link link_t;

struct link
{
  elem_t elem;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
  element_copy_fun copy_f;
  element_free_fun free_f;
  element_comp_fun cmp_f;
  int size;
};


elem_t list_no_copy(elem_t elem)
{
  return elem;
}

/// Creates a new list 
///
/// \param copy (may be NULL) a function applied to all elements when stored in the list
/// \param free (may be NULL) used to free elements in list_delete
/// \param compare (may be NULL) used to compare elements in list_contains
/// \returns: empty list
list_t *list_new(element_copy_fun copy, element_free_fun free, element_comp_fun compare)
{
  list_t *list = calloc(1, sizeof(list_t));
  list->free_f = free;
  if (copy)
  {
    list->copy_f = copy;    
  }
  else
  {
    list->copy_f = list_no_copy;
  }
  list->cmp_f  = compare;

  return list;
}

link_t *link_new(elem_t elem, link_t *next)
{
  link_t *link = calloc(1, sizeof(link_t));
  link->elem = elem;
  link->next = next;
  return link;
}

int adjust_index(int index, int size)
{
  /// Negative indexes count from the back
  if (index < 0)
    {
      /// Call adjust_index again to handle when
      /// adjusted index is still negative
      return adjust_index(size + index, size);
    }

  /// Index too big, adjust to after last element
  if (index > size)
    {
      return size;
    }

  /// Index OK
  return index;
}

link_t **list_find(list_t *list, int index)
{
  index = adjust_index(index, list->size);
  
  link_t **c = &(list->first);
  int counter = 0;
  while (*c && index > counter) {
    c = &((*c)->next);
    ++counter;
  }
  return c; // elementet som ska komma efter indexet vi söker
}

/// Inserts a new element at a given index. 
///
/// If list's copy function is non-NULL, it will be applied to elem and its result
/// stored in the list. Otherwise, elem will be stored in the list. 
///
/// All indexes are valid. 0 means first element. Negative indexes
/// count backward and too large negative indexes equal 0. Too
/// large positive indexes are same as -1.
/// 
/// \param list  pointer to the list
/// \param index the index for elem to be inserted at
/// \param elem  the element to be inserted
/// \returns true if succeeded, else false
void list_insert(list_t *list, int index, elem_t elem)
{
  if (list->size == 0) {
    list->first = link_new(elem, NULL);
    list->last = list->first;
  }
  else
  {  
    link_t **c = list_find(list, index);
    *c = link_new(list->copy_f(elem), (*c));
  }
  ++(list->size);
}

bool empty_list(list_t *list)
{
  return (!list->first);
}

/// Inserts a new element at the end of the list.
///
/// If list's copy function is non-NULL, it will be applied to elem and its result
/// stored in the list. Otherwise, elem will be stored in the list. 
///
/// \param list pointer to the list
/// \param elem the element to be appended
void list_append(list_t *list, elem_t elem)
{
  list_insert(list, -1, elem);
}
/// Inserts a new element at the beginning of the list
///
/// If list's copy function is non-NULL, it will be applied to elem and its result
/// stored in the list. Otherwise, elem will be stored in the list. 
///
/// \param list pointer to the list
/// \param elem the element to be prepended
void list_prepend(list_t *list, elem_t elem)
{
  list_insert(list, 0, elem);
}
/// Removes an element from a list.
///
/// All indexes are valid. 0 means first element. Negative indexes
/// count backward and too large negative indexes equal 0. Too
/// large positive indexes are same as -1.
/// 
/// \param list  pointer to the list
/// \param index the index to be removed
/// \param delete if true, run list's free function on all elements
/// \returns true if succeeded, else false
void list_remove(list_t *list, int index, bool delete)
{
  return;
}
/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returned
/// \param result pointer to where the element at index index will be stored if true is returned
/// \returns true if index was a valid index
bool list_get(list_t *list, int index, elem_t *result)
{
  link_t **c = list_find(list, index);
  *result = (*c)->elem;
  return (abs(index < list->size));
}
/// A convenience for list_get(list, 0, result)
bool list_first(list_t *list, elem_t *result)
{
  return false;
}

/// A convenience for list_get(list, -1, result)
bool list_last(list_t *list, elem_t *result)
{
  return false;
}

/// Returns the length of the list. It is undefined
/// whether the length is calculated in O(n) time or
/// whether there is a size counter in the list object
/// that is manipulated by insert, remove, etc. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list)
{
  return list->size;
}

/// Deletes a list. 
///
/// \param list pointer to the list
/// \param delete if true, use list's free function to free elements
void list_delete(list_t *list, bool delete)
{
  return;
}

/// Applies a function to all elements in a list in list order
///
/// \param list the list
/// \param fun the function to apply to all elements
/// \param data an extra argument passed to each call to fun (may be NULL)
/// \returns the result of all fun calls, combined with OR (||)
bool list_apply(list_t *list, elem_apply_fun fun, void *data)
{
  return false;
}

/// Searches for an element in a list
///
/// Uses list's compare if non-NULL, otherwise uses == for comparison. 
///
/// \param list the list
/// \param elem the element to search for
/// \returns the index of elem in list, or -1 if not found
int list_contains(list_t *list, elem_t elem)
{
  return 1;
}
