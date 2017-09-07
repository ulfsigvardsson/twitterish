#ifndef DB_H
#define DB_H

struct item {
  char *name;
  char *descr;
  int price;
  char *shelf;
};

typedef struct item item_t;

item_t make_item(char *name, char *descr, int price, char *shelf);
item_t input_item();
char *ask_question_shelf(char *question);
bool is_valid_shelf(char *str);
int add_to_string(char *arr[], char *buf, int index);
char *magick(char *arr1[], char *arr2[], char *arr3[]);
int add_to_string(char *arr[], char *buf, int index);
void list_db(item_t *items, int no_items);
void edit_db(item_t *items, int no_items);
void remove_item_from_db(item_t *db, int *db_size, int buf_size);
void add_item_to_db(item_t *db, int *db_size, int buf_size);

#endif
