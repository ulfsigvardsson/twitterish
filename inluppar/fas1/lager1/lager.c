#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "db.h"
#include "list.h"
#include "tree.h"

#define SIZE 16

void cp(char *source, char*dest);
void cat(char *filename, int *row);
void print_menu();
char ask_question_menu();
void event_loop(tree_t *db);






int main(int argc, char *argv[]) {
  char *keys[] = {"d", "b", "a", "c", "f", "e"};
  int elems[] = {4, 2, 1, 3, 6, 5};
  tree_t *tree = tree_new();
  for (int i=0; i < 6; ++i) {
    tree_insert(tree, keys[i], elems[i]);
  }
  int size = tree_size(tree);
  printf("size of tree: %d\n", size);

  int depth =  tree_depth(tree);
  printf("Depth of tree %d\n", depth);
  
  
  printf("Med nyckeln %s får vi elementet: %d\n", keys[2], elems[2]);

  T *elements = tree_elements(tree);
  for ( int i = 0; i < 6; ++i) {
    printf("Namn på element %d: %d\n", i, elements[i] ); 
  }
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

