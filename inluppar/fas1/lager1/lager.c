#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"
#include "shelfinfo.h"

// list_apply-funktion. Avgör om en hyllas namn är identisk med en sträng
void shelf_is_equal(L elem, void *data) {
  char *shelf_to_add = info_shelf(data);
  if (strcmp(shelf_to_add, shelf_id(elem)) == 0) {
    set_info_exist(true, data);
  }
}

// tree_apply-funktion. Avgör om ett elements hyllista innehåller en viss hylla
void item_has_shelf(K key, T elem, void *data) {
  L shelves = item_shelves(elem);
  list_apply(shelves, shelf_is_equal, data);
  if  (info_exists(data)) {
    // Om hyllan finns i listan kollar vi om hyllans 'ägare'
    // är samma vara som vi försöker lägga till/ändra i och sätter
    // ägaren till motsvarande värde.
    if (strcmp(key, info_name(data)) == 0) {
      enum owner owner = SELF;
      set_info_owner(data, owner);
    }
    else {
      enum owner owner = OTHER;
      set_info_owner(data, owner);
    } 
  }
}

// Kollar om ett hyllnamn finns i databasen, tar en shelf_info_t-pekare
// som lagrar hyllans ägare om den finns.
// returns: true om hyllan finns, annars false
bool shelf_is_used(tree_t *db, shelf_info_t *info) {
  enum tree_order order = inorder;
  tree_apply(db, order, item_has_shelf, info);
  return info_exists(info);
}

void check_shelf_ownership(tree_t *db, char *id, shelf_info_t *info, char *name) {
  set_info_name(info, name);
  set_info_shelf(info, id);
  shelf_is_used(db, info);
}

// Kontrollerar om ett hyllnamn finns med i en lista av hyllor, tar en int-pekare
/// som argument för att räkna ut index om det finns. Index måste vara -1 vid anrop.
/// Denna har lite annorlunda funktionalitet än shelf_is_used och får var kvar för stunden.
bool in_list(list_t *list, char *name_lookup, int *index) {
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
  if (tree_has_key(db, name)) {
    
    // Om varan redan finns i databasen väljer vi vilken hylla vi vill lägga in på
    T item = tree_get(db, name);
    printf("Varan finns redan i databasen.\n");
    print_item(item);
    char *shelf        = ask_question_shelf("Välj en ny eller befintlig hylla: ");
    int amount         = ask_question_int("Välj antal att lagra: "); // här kan vi lägga till ett argument till ask_question_int som skriver ut namnet på elementet/hyllan
    shelf_t *new_shelf = shelf_new(shelf, amount);
    list_append(item_shelves(item), new_shelf);
  }
  else {

    // Annars gör vi en ny vara
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


void edit_shelves(tree_t *db, T item, char choice, char *name) {
  list_t *list_of_shelves;
  char *shelf_to_edit;
  int index;
  L shelf_to_remove;
  
  // Loop tills man valt en av  hyllorna i varans lista 
  do {
    index = -1;
    list_of_shelves = item_shelves(item);
    shelf_to_edit = ask_question_shelf("Välj en hylla: ");
  } while (!in_list(list_of_shelves, shelf_to_edit, &index));

  list_remove(list_of_shelves, index, &shelf_to_remove); // Tar bort vald hylla och lägger i shelf_to_remove
  printf("Nuvarande hylla: %s\n"\
         "---------------------\n", shelf_to_edit);

  if (choice == 'L' ) {
    // Om vi har valt att ändra namn på en lagerhylla
    shelf_info_t *info = shelf_info_new();
    char *new_id = ask_question_shelf("Ange ny hylla: ");
    check_shelf_ownership(db, new_id, info, name);

    // Om någon annan vara ligger på vald hylla får vi välja en ny
    if (info_owner(info) == OTHER) {
      do {
        new_id = ask_question_shelf("Vald hylla innehåller annan vara, gör ett nytt val: ");
        set_info_owner(info, NONE); // Nollställer ägandeskapet
        set_info_shelf(info, new_id); // Uppdaterar hyllan till det nya valet      
      } while (info_owner(info) == OTHER);
    }

    int amount = shelf_amount(shelf_to_remove);
    shelf_t *new_shelf = shelf_new(new_id, amount);
    list_insert(list_of_shelves, index, new_shelf);
  }
  else {
    // Ändra antal varor på en lagerhylla
    int amount = ask_question_int("Ange nytt antal: ");
    char *new_id = shelf_id(shelf_to_remove);
    shelf_t *new_shelf = shelf_new(new_id, amount);
    list_insert(list_of_shelves, index, new_shelf);
  }
  free(shelf_to_remove); // Osäker
}

void edit_db(tree_t *db) {
  list_db(db);
  char *name = ask_question_string("Välj vara att redigera: ");

  // Om inte varan finns i databasen får användaren försöka igen
  while (!tree_has_key(db, name)) {
    printf("Ogiltigt val: \"%s\". ", name);
    name = ask_question_string("Gör ett nytt val: \n");
  }
  
  T item = tree_get(db, name); // Det valda lagerobjektet
  print_item(item);
  char *menu = "\n[B]eskrivning\n"              \
               "[P]ris\n"\
               "[L]agerhylla\n"\
               "An[t]al\n\n"\
               "Välj rad eller [a]vbryt: ";

  char edit_choice = ask_question_menu(menu, "BbPpLlTtAa");

  switch (edit_choice) {
    case 'A': { return;}
    case 'P': {
      printf("Nuvarande pris: %d\n"                                     \
             "------------------\n", item_price(item));
      int new_price = ask_question_int("Nytt pris: ");
      edit_price(item, new_price);
      break;
    }
    case 'B': {
      printf("Nuvarande beskrivning: %s\n"\
             "-------------------------\n", item_descr(item));
      char *new_descr = ask_question_string("Ny beskrivning: ");
      edit_description(item, new_descr);
      break;
    }
    // Samlar case för Lagerhylla och Antal då de båda behandlar hyllor
    default : {
      edit_shelves(db, item, edit_choice, name);
    }// OBS! Måste frigöra minne för shelf_info_new
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


