#ifndef DB_H
#define DB_H
#include "tree.h"
#include "list.h"

struct shelf {
  char *id;
  int amount;
};

struct item {
  char *name;
  char *descr;
  int price;
  list_t *shelves;
};

typedef struct shelf shelf_t;
typedef struct item item_t;
typedef struct pair { item_t *edited; item_t original; } pair_t;

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } type;
  pair_t p;
};

typedef struct action action_t;


item_t *make_item(char *name, char *descr, int price);
void list_db(tree_t *items);
void edit_db(tree_t *db, action_t *last_action);
void remove_item_from_db(tree_t *db, action_t *last_action);
void add_item_to_db(tree_t *db);
char ask_question_menu(char *menu, char *menu_choices);
item_t *create_db(int size);
void undo_last_action(action_t *last_action, tree_t *db);
#endif

