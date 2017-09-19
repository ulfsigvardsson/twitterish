#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"


void print_menu();
char ask_question_menu();
void event_loop(tree_t *db);


int main(int argc, char *argv[]) {
  char *name = "Hammare";
  char *descr = "Ett verktyg";
  int price = 15;
  char *shelf_id = "A12";
  int amount = 1;

  item_t *new_item = item_new(name, descr, price, shelf_id, amount);
  item_t *new_item2 = item_new("Bajs", "Kiss", 1, "D23", 4);
  tree_t *tree = tree_new();
  tree_insert(tree, new_item->name, *new_item);
  tree_insert(tree, new_item2->name, *new_item2);
  char **keys = tree_keys(tree);

  for (int i = 0; i < 2; ++i) {
    printf("Keys: %s\n", *keys);  
  }
  
  int size = tree_size(tree);
  printf("Storlek på trädet: %d\n", size);
  return 0;
}


// Huvudloop för programmet. 

void event_loop(tree_t *db) {
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


