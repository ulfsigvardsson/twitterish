#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"

typedef struct pair { item_t *edited; item_t original; } pair_t;

struct action
{
  enum { NOTHING, ADD, REMOVE, EDIT } type;
  pair_t p;
};

typedef struct action action_t;


void print_menu();
char ask_question_menu();
void event_loop(tree_t *db);
void list_db(tree_t *tree);
void print_item(T elem);


  
void undo_last_action(action_t *last_action, tree_t *db) {
  return;
}

tree_t *create_db() {
  return tree_new();
}

void remove_item_from_db(tree_t *db, action_t *last_action) {
  printf("Inte implementerad\n");
  return;
}

// Lägger till en vara i databasen
//TODO: Om varan redan finns ska man få välja en ny eller gammal  hylla att sätta in den på.
void add_item_to_db(tree_t *db) {
  char *name  = ask_question_string("Ange namn på vara:\n");
  char *descr = ask_question_string("Ange en beskrivning av varan:\n");
  int price   = ask_question_int("Ange pris på varan:\n");
  char *shelf = ask_question_shelf("Ange hyllplats:\n");
  int amount  = ask_question_int("Ange antal: \n");
  item_t *item = item_new(name, descr, price, shelf, amount);
  tree_insert(db, item->name, *item);
}

void edit_db(tree_t *db, action_t *last_action) {
  char *choice;
  list_db(db);
 
  do {
    choice = ask_question_string("Ange namn för varan du vill ersätta\n");
  } while (!tree_has_key(db, choice));

   item_t item = tree_get(db, choice);
   print_item(item);

  while (true) {
    choice = ask_question_string("Ange vilken del du vill ersätta\n");

    if (strcmp("B", choice) == 0) {
      char *new_desc = ask_question_string("Ange ny beskrivning\n");
      item.descr = new_desc;
      break;
    }  
    else if (strcmp("P", choice) == 0) {
      int new_price = ask_question_int("Ange nytt pris\n");
      item.price = new_price;
      break;
    }
    else if (strcmp("H", choice) == 0) {
      printf("Inte implementerad\n");
      break;
    }
  }
}


// list_action2-funktion för print_shelves()
void print_shelf(L shelf, void *data) {
  shelf_t *tmp;
  tmp = (shelf_t*)shelf;
  printf("[%s]: %d st.\n", tmp->id, tmp->amount);
}

// Skriver ut alla hyllor i en lista
void print_shelves(list_t *list) {
  printf("Hyllor:  ");
  list_apply(list, print_shelf, NULL);
}

// Skriver ut en varas detaljinformation
void print_item(T elem) {
  printf("%s\n"\
         "[B]eskrivning: %s\n"\
         "[P]ris: %d\n", elem.name, elem.descr, elem.price);
  print_shelves(elem.shelves);
}

// Hjälpfunktion til list_db.
// Skriver ut index följt av varans namn.
void list_db_aux(K key, T elem, void *data) {
  printf("%d: %s\n", *(int*)data, elem.name);
  ++(*(int*)data); // Varans index i databasen
}


// skriver ut alla varor i databasen på formen
// 1. Namn1
// 2. Namn2
// ...
// N. NamnN
void list_db(tree_t *tree) {
  enum tree_order order = inorder;
  int index = 1;
  tree_apply(tree, order, list_db_aux, &index);
}

// Huvudloop för programmet. 

void event_loop(tree_t *db) {
  char user_choice;
  action_t undo = { .type = NOTHING };
  char *menu = "\n[L]ägga till en vara\n"\
                 "[T]a bort en vara\n"\
                 "[R]edigera en vara\n"\
                 "Ån[g]ra senaste ändringen\n"\
                 "Lista [h]ela varukatalogen\n"\
                 "[A]vsluta\n\n";
  
    do {
      print_menu(menu);
      user_choice = toupper(ask_question_menu("Ange ett menyval: ", "LTRGHA"));
 
      switch (user_choice) {
        case 'L': {add_item_to_db(db);
                   undo.type = ADD;
                   break;}
        case 'T': {remove_item_from_db(db, &undo); break;}
        case 'R': {edit_db(db, &undo);             break;}
        case 'G': {undo_last_action(&undo, db);    break;}
        case 'H': {list_db(db);                    break;}
        default:  printf("Avslutar...\n");         break;}
    } while (user_choice != 'A');
  
}

int main(int argc, char *argv[]) {
  tree_t *db = create_db();
  event_loop(db);
  return 0;
}
