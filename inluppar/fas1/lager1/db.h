#ifndef DB_H
#define DB_H


struct shelf {
  char *id;
};

typedef struct shelf shelf_t;

struct item {
  char *name;
  char *descr;
  int price;;
  int amount;
  shelf_t shelf; // Ska vara en lista av shelves
};

typedef struct item item_t;
typedef struct pair { item_t *edited; item_t original; } pair_t;

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } type;
  pair_t p; // EDIT
};

typedef struct action action_t;


item_t make_item(char *name, char *descr, int price, shelf_t shelf, int amount);
char *magick(char *arr1[], char *arr2[], char *arr3[]);
void list_db(item_t *items, int no_items);
void edit_db(item_t *items, int no_items, action_t *last_action);
void remove_item_from_db(item_t *db, int *db_size, action_t *last_action);
void add_item_to_db(item_t *db, int *db_size, int buf_size);
char ask_question_menu(char *menu, char *menu_choices);
item_t *create_db(int size);
void undo_last_action(action_t *last_action, item_t *db, int *db_size);
#endif

