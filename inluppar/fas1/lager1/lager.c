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
void event_loop(item_t *db, int *db_size, int buf_size);



  struct node {
  K key;    
  list_t *l;  
};

struct tree {
  node_t *node;
  tree_t *left;
  tree_t *right;
};





int main(int argc, char *argv[]) {
  /*
  list_t *lista = list_new();
  L elem;
  for (int i = 0; i < 5; ++i) {
    list_append(lista, i);
  }
  
  printf("Originallistan: \n");
  print_list(lista);
  list_remove(lista, 0, &elem);
  printf("Efter att ha tagit bort index 0\n");
  print_list(lista);
  L test = list_get(lista, 1);
  printf("Elementet på index 1: %d\n", test);
  elem = list_first(lista);
  printf("Första elementet: %d\n", elem);
  elem = list_last(lista);
  printf("Sista elementet: %d\n", elem);
  list_insert(lista, 3, 9);
  printf("efter insert:\n");
  print_list(lista);
  */





  
  tree_t *new_tree = tree_new();
  //new_tree->node = node_new();
  //new_tree->right = tree_new();
  //new_tree->left = tree_new();
  //new_tree->right->node = node_new();
  //new_tree->left->node = node_new();
  //new_tree->right->right = tree_new();
  //new_tree->right->right->node = node_new();
  int size = tree_size(new_tree);
  printf("size of tree: %d\n", size);

  int depth = tree_depth(new_tree);
  printf("Depth of tree %d\n", depth);
  

  int buf_size = SIZE;
  item_t db[SIZE];  // Databas med plats för 16 objekt
  int db_size = 0;
  event_loop(db, &db_size, buf_size);
  return 0;
}

// Kopierar en sträng från en pekare till en annan adress
void cp(char *source, char *dest) {
  FILE *s = fopen(source, "r");
  FILE *d = fopen(dest, "w");
  int c   = fgetc(s);
 
  while (c != EOF) {
    fputc(c, d);
    c = fgetc(s);
  }
  fclose(s);
  fclose(d);
}

// Skriver ut innehållet i en textfil på skärmen
void cat(char *filename, int *row) {
  printf("==== %s ====\n", filename);
  FILE *f = fopen(filename, "r");
  int c   = fgetc(f);
  printf("%d. ", *row);
  
  while (c != EOF)
  { 
    // Om karaktären är newline ökas radräknaren och skrivs
    // ut OM det inte är den sista raden i filen
    if (c == '\n') {
      ++*row;
      fputc(c, stdout);
      c = fgetc(f);  // fgetc() popar också c från input buffern
      if (c != EOF) {
        printf("%d. ", *row);
      }
    }
    else {
      fputc(c, stdout);
      c = fgetc(f);
    }
  }
  fclose(f);
}

// Huvudloop för programmet. ACHIEVEMENT: vädeöverföring via pekare görs med pekare till db

void event_loop(item_t *db, int *db_size, int buf_size) {
  char user_choice;
  action_t undo ={ .type = NOTHING };
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
      case 'L': {add_item_to_db(db, db_size, buf_size);
                   undo.type = ADD;
                   break;}
        case 'T': {remove_item_from_db(db, db_size, &undo);    break;}
        case 'R': {edit_db(db, *db_size, &undo);               break;}
        case 'G': {undo_last_action(&undo, db, db_size);       break;}
        case 'H': {list_db(db, *db_size);                      break;}
        default:  printf("Avslutar...\n");                     break;}
    } while (user_choice != 'A');
}  


