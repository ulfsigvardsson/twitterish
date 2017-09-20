#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"

void print_menu();
void event_loop(tree_t *db);

// list_apply-funktion. Skriver ut en enskild hylla.
void print_shelf(L elem, void *data) {
  printf("%s       %d\n", shelf_id(elem), shelf_amount(elem));
}

// Hjälpfunktion till print_item(). Skriver ut alla hyllor
void print_shelves(list_t *list) {
  printf("Hylla    Antal\n");
  list_apply(list, print_shelf, NULL);
}

// Skriver ut all info om en vara på skärmen
void print_item(T item) {
  printf("=====VARUSPECIFIKATION====\n"\
         "Namn: %s\n"\
         "Beskrivning: %s\n"\
         "Pris: %d\n",
         item_name(item), item_descr(item), item_price(item));
  print_shelves(item_shelves(item));
}
// Hjälpfunktion til list_db.
// Skriver ut index följt av varans namn.
void list_db_aux(K key, T elem, void *data) {
  printf("%d: %s\n", *(int*)data, item_name(elem));
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

void db_add_item(tree_t *db) {
  char *name = ask_question_string("Ange namn: ");
  if (tree_has_key(db, name)) { // Om varan redan finns i databasen
    T item = tree_get(db, name);
    printf("Varan finns redan i databasen.\n");
    print_item(item);
    char *shelf        = ask_question_shelf("Välj en ny eller befintlig hylla: ");
    int amount         = ask_question_int("Välj antal att lagra: "); // här kan vi lägga till ett argument till ask_question_int som skriver ut namnet på elementet/hyllan
    shelf_t *new_shelf = shelf_new(shelf, amount);
    list_append(item_shelves(item), new_shelf);
  }
  else { // Annars gör vi en ny vara
    char *descr  = ask_question_string("\nAnge beskrivning: ");
    int price    = ask_question_int("\nAnge pris: ");
    char *shelf  = ask_question_shelf("Välj en ny eller befintlig hylla: ");
    int amount   = ask_question_int("Välj antal att lagra: ");
    item_t *item = item_new(name, descr, price, shelf, amount);
    tree_insert(db, name, item);
  }
}

void db_remove_item(tree_t *db) {
  return;
}

void edit_db() {
  return;
}

void undo_last_action() {
  return;
}

void event_loop(tree_t *db) {
  char user_choice;
  char *menu = "\n[L]ägga till en vara\n"\
                 "[T]a bort en vara\n"\
                 "[R]edigera en vara\n"\
                 "Ån[g]ra senaste ändringen\n"\
                 "Lista [h]ela varukatalogen\n"\
                 "[A]vsluta\n\n";
  
  do {
    printf("%s\n", menu);
    user_choice = toupper(ask_question_menu("Ange ett menyval: ", "LTRGHA"));

    switch (user_choice) {
      case 'L': {db_add_item(db);                break;}
      case 'T': {db_remove_item(db);             break;}
      case 'R': {edit_db(db);                    break;}
      case 'G': {undo_last_action();             break;}
      case 'H': {list_db(db);                    break;}
      default:  printf("Avslutar...\n");         break;}
} while (user_choice != 'A');

  /*char user_choice;
  action_t undo = { .type = NOTHING };
  char *menu = "\n[L]ägga till en vara\n"\
                 "[T]a bort en vara\n"\
                 "[R]edigera en vara\n"\
                 "Ån[g]ra senaste ändringen\n"\
                 "Lista [h]ela varukatalogen\n"\
                 "[A]vsluta\n\n";
  
    do {
      // skickar db_size som pointer i fallen då den måste justeras, ta M38 här och visa att db_size allokeras på stacken och skickas över funktioner
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
  */}  


/*
void print_item(K key, T elem, void *data) {
  printf("Index: %d\n"\
         "Namn: %s\n"                           \
         "Beskrivning: %s\n"\
         "Pris: %d\n"\
         , *(int*)data, key, elem.descr, elem.price);
  ++(*(int*)data);
  }*/

int main(int argc, char *argv[]) {
  char *name = "Hammare";
  char *descr = "Ett verktyg";
  int price = 15;
  char *shelf_id = "A12";
  int amount = 1;

  item_t *i1 = item_new(name, descr, price, shelf_id, amount);
  item_t *i2 = item_new("Banan", "En frukt", 13, "A2", 100);

  tree_t *db = tree_new();
  tree_insert(db, item_name(i1), i1);
  tree_insert(db, item_name(i2), i2);


  event_loop(db);
  return 0;
}
