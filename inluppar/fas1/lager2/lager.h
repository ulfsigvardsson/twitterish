#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shelfinfo.h"
#include "utils.h"
#include "common.h"
#include "list.h"
#include "tree.h"
#include "item.h"

typedef enum last_action {NOTHING, ADD, REMOVE, EDIT} last_action_t;

typedef struct undo_action
{
  elem_t added;
  elem_t removed;
  elem_t edit_old;
  elem_t edit_new;
  last_action_t last_action;
} undo_action_t;

undo_action_t *undo_new();
void undo_reset(undo_action_t *undo);
bool shelf_is_equal(elem_t shelf, void *info);
bool shelf_is_in_list(elem_t key, elem_t item, void *info);
void merge_shelves(shelf_info_t *info, elem_t shelf_to_edit, list_t *shelves, int index);
