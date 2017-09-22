#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"

void print_menu();
void event_loop(tree_t *db);


enum state {BLOCKED, FREE, SAME};


typedef struct save_info {
  bool exists;
  enum state state;
  char *name;
  char *id;
} save_info_t;

save_info_t *save_info_new() {
  save_info_t *new = calloc(1, sizeof(save_info_t));
  return new;
}

bool info_exists(save_info_t *info) {
  return info->exists;
}

enum state info_state(save_info_t *info) {
  return info->state;
}

char *info_name(save_info_t *info) {
  return info->name;
}

char *info_id(save_info_t *info) {
  return info->id;
}

void set_info_exist(bool val, save_info_t *info) {
  info->exists = val;
}

void set_info_state(enum state state, save_info_t *info) {
  info->state = state;
}

void set_info_name(char *name, save_info_t *info) {
  info->name = name;
}


void set_info_id(char *id, save_info_t *info) {
  info->id = id;
}



void shelf_is_equal(L elem, void *data) {
  char *name = info_id(data);
  if (strcmp(name, shelf_id(elem)) == 0) {
    set_info_exist(true, data);
  }
}

void shelf_check_func(K key, T elem, void *data) {
  L shelves = item_shelves(elem);
  list_apply(shelves, shelf_is_equal, data);
  if  (info_exists(data)) {
    if (strcmp(key, item_name(elem)) == 0) {
       enum state state = SAME;
       set_info_state(state, data);
    }
    else {
      enum state state = BLOCKED;
      set_info_state(state, data);
    } 
  }  
}

void tree_has_shelf(tree_t *db, save_info_t *info) {
  enum tree_order order = inorder;
  tree_apply(db, order, shelf_check_func, info);
}

// =======================================


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

save_info_t *info_initiate(void) {
  save_info_t *info = save_info_new();
  set_info_exist(false, info);
  set_info_state(FREE, info);
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
     char *id;
     save_info_t *info = info_initiate();
     do {
         set_info_exist(false, info);
         id = ask_question_shelf("Ange ny hylla: ");
         set_info_id(id, info);
         tree_has_shelf(db, info);
          }
       while (info_exists(info));
       if (!info_exists(info)) {      
         char *descr  = ask_question_string("\nAnge beskrivning: ");
         int price    = ask_question_int("\nAnge pris: ");
         int amount   = ask_question_int("Välj antal att lagra: ");
         item_t *item = item_new(name, descr, price, id, amount);
         tree_insert(db, name, item);
        }
   }
}

void db_remove_item(tree_t *db) {
  return;
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
    
    list_t *shelves;
    char *id;
    int index = -1;
    L old_shelf;
    save_info_t *info = info_initiate();
    // Loop tills man valt en befintlig hylla
    do {
      index = -1;
      shelves = item_shelves(item);
      id = ask_question_shelf("Välj en hylla: ");
    } while (!has_shelf(shelves, id, &index));

    printf("Nuvarande hylla: %s\n"\
         "-----------------------------------------------------\n", id);
    list_remove(shelves, index, &old_shelf);
    
    if (edit_choice == 'L') {
       do {
         set_info_exist(false, info);
         id = ask_question_shelf("Ange ny hylla: ");
         set_info_id(id, info);
         tree_has_shelf(db, info);
          }
       while (info_exists(info));
       if (!info_exists(info)) {          
          int amount = shelf_amount(old_shelf);
          shelf_t *new_shelf = shelf_new(id, amount);
          list_insert(shelves, index, new_shelf);
          return;
       }
       else {
         return;
       }
    }
    else {   // edit_choice == t
        int amount = ask_question_int("Välj ett nytt antal: ");
        id = shelf_id(old_shelf);
        shelf_t *new_shelf = shelf_new(id, amount);
        list_append(shelves, new_shelf);
        return;
        
    }
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
      case 'H': {list_db(db);                    break;}
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

