#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"
#include "saveinfo.h"

void print_menu();
void event_loop(tree_t *db);


void shelf_is_equal(L elem, void *data) {
  char *new_shelf_id = info_id(data);
  if (strcmp(new_shelf_id, shelf_id(elem)) == 0) { 
    set_info_exists(true, data);
  }
}
void shelf_check_func(K key, T elem, void *data) {
  L shelves = item_shelves(elem);
  // //nollställer inför varje lista
  list_apply(shelves, shelf_is_equal, data);
  if  (info_exists(data)) {
    set_info_exists(false, data);
    if (strcmp(key, info_name(data)) == 0) {
       set_info_owner(SELF, data);
    }
    else {
      set_info_owner(OTHER, data);
    } 
  }
}

// Lagrar ägarinformation om en hylla i 'info': SELF, OTHER eller NONE
void find_shelf_owner(tree_t *db, save_info_t *info) {
  tree_apply(db, inorder, shelf_check_func, info);
}

// Kontrollerar om ett hyllnamn finns med i en lista av hyllor, tar en int-pekare
/// som argument för att räkna ut index om det finns. Index måste vara -1 vid anrop.
bool has_shelf(list_t *list, char *name_lookup, int *index) {
  for (int i = 0; i < list_length(list); ++i) {
    ++(*index);
    L *temp_shelf = list_get(list, i); // L-pekare som avrefereras och skickas till shelf_id som tar en L
    if (strcmp(shelf_id(*temp_shelf), name_lookup) == 0) {
      return true;
    }
  }
  return false;
}

// list_apply-funktion. Skriver ut en enskild hylla.
void print_shelf(L elem, void *data) {
  printf("%s  \t %d\n", shelf_id(elem), shelf_amount(elem));
}

// Hjälpfunktion till print_item(). Skriver ut alla hyllor
void print_shelves(list_t *list) {
  printf("Hylla \t Antal\n");
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

save_info_t *info_initiate(void) {
  save_info_t *info = save_info_new();
  set_info_exists(false, info);
  set_info_owner(NONE, info);
  set_info_name(NULL, info);
  set_info_id(NULL, info);
  return info;
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
void list_db(tree_t *db) {
  if (!db) {
    printf("Tom databas!\n");
    return;
  }
  else {
    enum tree_order order = inorder;
    int index = 1;
    tree_apply(db, order, list_db_aux, &index);
    
  }
}

void list_db2(tree_t *db) {
  if (!db) {
    printf("Tom databas!\n");
    return;
  }
  else {
    int size = tree_size(db);
    K *list_of_keys = tree_keys(db);
    while (size > 0) {
      int i = 1;
      while (i < 3 && size > 0) {
        printf("%d. %s\n", i, *list_of_keys);
        ++list_of_keys;
        ++i;
        --size;
      }
      if (size > 0) {
        char yes_or_no = ask_question_menu("\nVill du se fler varor, [J]a eller [N]ej?\n", "JjNn");
        if (yes_or_no == 'N') {
          return;
        }
        else {
          putchar('\n');
        }  
      }
    }
  }
}

void db_remove_item(tree_t *db) {
  return;
}

// Låter användaren välja en ny hylla tills en som är ledig eller tillhör samma vara är vald
char *input_new_shelf(tree_t *db, save_info_t *info) {
  char *new_id;
  do {
    if (info_owner(info) == OTHER) {
      printf("Hyllan är upptagen!\n");
    }
    new_id = ask_question_shelf("Ange ny hylla: ");
    set_info_exists(false, info);
    set_info_owner(NONE, info);
    set_info_id(new_id, info);
    find_shelf_owner(db, info); // lägger till ägandeinformation om hyllan i info
  } while (info_owner(info) == OTHER);
  return new_id;
}
void shelf_add_amount(list_t *shelves, char *id, int amount) {
  int index = -1;                       //Lägger till amount till id:s amount och insertar.
  L old_shelf2;
  has_shelf(shelves, id, &index);
  list_remove(shelves, index, &old_shelf2);
  int amount2 = shelf_amount(old_shelf2);
  shelf_t *new_shelf = shelf_new(id, (amount+amount2));
  list_insert(shelves, index, new_shelf);
}

void db_add_item(tree_t *db) {
  save_info_t *info = info_initiate();
  char *name = ask_question_string("Ange namn: ");
  set_info_name(name, info); // Lagrar varunamnet i 'info'

  if (tree_has_key(db, name)) {               // Om varan redan finns i databasen
    T item = tree_get(db, name);
    list_t *shelves = item_shelves(item);
    printf("Varan finns redan i databasen.\n");
    print_item(item);
    char *id = input_new_shelf(db, info);

    // Om input_new_shelf sätter info.owner till SELF
    if (info_owner(info) == SELF) {
      printf("Du valde att lägga till på hylla %s.\n", id);
      int amount = ask_question_int("Välj antal att lägga till: ");
       shelf_add_amount(shelves, id, amount);
    }

    // Om input_new_shelf sätter info.owner till NONE    
    else {
      int amount = ask_question_int("Välj antal att lagra: ");
      shelf_t *new_shelf = shelf_new(id, amount);
      list_append(shelves, new_shelf);
    }
  }
  else {        // Annars gör vi en ny vara
    char *descr  = ask_question_string("\nAnge beskrivning: ");
    int price    = ask_question_int("\nAnge pris: ");
    char *new_id = input_new_shelf(db, info);
    int amount   = ask_question_int("Välj antal att lagra: ");
    item_t *item = item_new(name, descr, price, new_id, amount);
    tree_insert(db, name, item);

   
  }
}


void edit_shelves(tree_t *db, item_t *item, char edit_choice) {
  // char *name = item_name(item);
    list_t *shelves;
    int index = -1;
    char *id;
    L old_shelf;
    save_info_t *info = info_initiate();
    set_info_name(item_name(item), info); // Lagra varunamnet i 'info'
    // Loop tills man valt en befintlig hylla
    do {
      index = -1;
      shelves = item_shelves(item);
      id = ask_question_shelf("Välj en hylla: ");
    } while (!has_shelf(shelves, id, &index));

    printf("Nuvarande hylla: %s\n"\
         "-----------------------------------------------------\n", id);
    list_remove(shelves, index, &old_shelf); //sparar den gamla hyllan i old_shelf
    
    if (edit_choice == 'L') {
       char *new_id = input_new_shelf(db, info);
       if (info_owner(info) == SELF) {
         
         printf("Du valde att slå ihop hyllorna %s och %s.\n", new_id, id);
         int amount = shelf_amount(old_shelf);
         shelf_add_amount(shelves, new_id, amount);
         
       }
       else {
         
         int amount = shelf_amount(old_shelf);
         shelf_t *new_shelf = shelf_new(new_id, amount);
         list_insert(shelves, index, new_shelf);
         return;
       }
    }
    else {   // edit_choice == t
      
        int amount = ask_question_int("Välj ett nytt antal: ");
        id = shelf_id(old_shelf);
        shelf_t *new_shelf = shelf_new(id, amount);
        list_insert(shelves, index,  new_shelf);
        return;
        
    }
}   

void edit_db(tree_t *db) {
  list_db(db);
  char *name = ask_question_string("Välj vara att redigera: ");

  while (!tree_has_key(db, name)) {
    printf("Ogiltigt val: \"%s\".", name);
    name = ask_question_string("Gör ett nytt val: \n");
  }
  
  T item = tree_get(db, name);
  print_item(item);
  char *menu_choices = "BbPpLlTtAa";
  char *menu = "\n[B]eskrivning\n"              \
               "[P]ris\n"\
               "[L]agerhylla\n"\
               "An[t]al\n\n"\
               "Välj rad eller [a]vbryt: ";

  char edit_choice = ask_question_menu(menu, menu_choices);
  switch (edit_choice) {
  case 'A': {
    return;
  }
  case 'P': {
    printf("Nuvarande pris: %d\n"\
           "-----------------------------------------------------\n", item_price(item));
    int new_price = ask_question_int("Nytt pris: ");
    edit_price(item, new_price);
    break;
  }
  case 'B': {
    printf("Nuvarande beskrivning: %s\n"\
           "-----------------------------------------------------\n", item_descr(item));
    char *new_descr = ask_question_string("Ny beskrivning: ");
    edit_description(item, new_descr);
    break;
  }
    // Samlar case för Lagerhylla och Antal då de båda behandlar hyllor
  default : {
    
    edit_shelves(db, item, edit_choice); 
  }                            // OBS! Måste frigöra minne för save_info_new
 }
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
      case 'H': {list_db2(db);                    break;}
      default:  printf("Avslutar...\n");         break;}
  } while (user_choice != 'A');
}
 
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

