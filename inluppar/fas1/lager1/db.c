/*
db.c -- database
Written on fredag,  1 september 2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "db.h"




//====PROTOTYPES====

void print_item(item_t *item);
bool is_menu_choice(char c, char *menu_choices);
void print_menu();
bool is_valid_shelf(char *str);
int add_to_string(char *arr[], char *buf, int index);
item_t input_item();
shelf_t to_shelf(char *shelf);
void edit_description(item_t *items, int index);
void add_item_to_db(item_t *db, int *db_size, int buf_size);
void edit_price(item_t *items, int index);
void edit_description(item_t *items, int index);
void edit_shelf(item_t *items, int index);
void save_item(item_t *db, int *db_size, item_t item);
void undo_last_action(action_t *saved_items, item_t *db, int *no_items);

//====FUNCTIONS====

// Skriver ut en enskild vara
void print_item(item_t *item) {
  int kronor = (item->price)/100;
  int oren   = (item->price)%100;
  shelf_t shelf = item->shelf;
  char *shelf_id = shelf.id;  // Inte allokerat plats, låter denna vara tills vidare
  printf("\n=====VARUSPECIFIKATION=====\n");
  printf("Namn: %s\n", item->name);
  printf("Beskrivning: %s\n", item->descr);
  printf("Pris: %d.%d SEK\n", kronor, oren);
  printf("Hylla: %s\n", shelf_id);
  printf("Antal: %d\n", item->amount);
}

shelf_t make_shelf(char *shelf) {
  shelf_t s = { .id = shelf };
  return s;
}

// Skapar en vara
item_t make_item(char *name, char *descr, int price, shelf_t shelf, int amount) {
  item_t item ={ .name   = name,
                 .descr  = descr,
                 .price  = price,
                 .shelf  = shelf,
                 .amount = amount };
  return item;
}

// Låter användaren mata in information om en vara och skapar en ny vara
item_t input_item() {
  char *name      = ask_question_string("Ange namn på vara: ");
  char *descr     = ask_question_string("\nAnge en beskrivning av varan: ");
  int price       = ask_question_int("\nAnge pris på varan :");
  char *shelf_c   = ask_question_shelf("\nAnge hyllplats :");
  shelf_t shelf_s = { .id = shelf_c };
  int amount      = ask_question_int("\nAnge antal varor :");
  item_t item     = make_item(name, descr, price, shelf_s, amount);
  return item;
}

// Väljer tre slumpmässiga ord från tre arrayer av strängar
// och sammanfogar dem till ett ord
char *magick(char *arr1[], char *arr2[], char *arr3[]) {
  char buf[255];
  int index = 0;
  index = add_to_string(arr1, buf, index);
  buf[index] = '-';
  ++index;
  index = add_to_string(arr2, buf, index);
  buf[index] = ' ';
  ++index;
  index = add_to_string(arr3, buf, index);
  buf[index] = '\0';
  return strdup(buf);
}

// Väljer en slumpmässig sträng från en array av strängar
// och lägger till den till *buf
int add_to_string(char *arr[], char *buf, int index) {
  int max      = 5;  // samma längd på alla arrays
  int rand_num = random() %max;
  char *word   = arr[rand_num];

  for (int j = 0; j < strlen(word); ++j) {
    buf[index] = word[j];
    ++index;
  }
  return index;
}

// Skriver ut namnen på alla objekt i en databas
void list_db(item_t *items, int no_items) {
  char *name;
  item_t item;
  printf("\n====DATABAS====\n");
  
  for (int i = 0; i < no_items; ++i) {
    item = items[i];
    name = item.name;
    printf("%d: %s\n" , i+1, name);
  }
  
  printf("\n");
}

// Editerar en databas
void edit_db(item_t *items, int no_items) {
  if (no_items == 0) {
    printf("\nInga objekt i databasen!\n\n");
    return;
  }
  else {
    int index;  // Index på varan att ändra
    list_db(items, no_items);
  
    do {
      index = ask_question_int("\nAnge index för varan du vill ersätta: ");
    } while (index < 1 || index > no_items);
  
    print_item(&items[index-1]);
  
    char *menu = "\n[B]eskrivning\n"\
                   "[P]ris\n"\
                   "[H]ylla\n"\
                   "Välj ett alternativ eller [a]vbryt: ";
    
    char choice = toupper(ask_question_menu(menu, "BbPpHhAa"));

    switch (choice) {
      case 'A': {                                 return;}
      case 'B': {edit_description(items, index-1); break;}
      case 'P': {edit_price(items, index-1);       break;}
      case 'H': {edit_shelf(items, index-1);       break;}
    }
  }
}

// Hjälpfunktion för edit_db, ändrar på objektsbeskrivningen
void edit_description(item_t *items, int index) {
  printf("Nuvarande beskrivning: %s\n", items[index].descr);
  printf("--------------------------------------------\n");
  char *new_desc = ask_question_string("Ny beskrivning: ");
  items[index].descr = new_desc;
}

// Hjälpfunktion för edit_db, ändrar på priset
void edit_price(item_t *items, int index) {
  printf("Nuvarande pris: %d\n", items[index].price);
  printf("--------------------------------------------\n");
  int new_price = ask_question_int("Ange nytt pris: ");
  items[index].price = new_price;
}

// Hjälpfunktion för edit_db, ändrar på hyllan
void edit_shelf(item_t *items, int index) {
  char *shelf_id = items[index].shelf.id;
  printf("Nuvarande hylla: %s\n", shelf_id);
  printf("--------------------------------------------\n");
  char *new_shelf_char = ask_question_shelf("Ange ny hylla: ");
  shelf_t new_shelf = {.id = new_shelf_char};
  items[index].shelf = new_shelf;
}

// Hjälpfunktion för edit_db, ändrar på antalet objekt
void edit_amount(item_t *items, int index) {
  printf("Nuvarande antal: %d\n", items[index].price);
  printf("--------------------------------------------\n");
  int new_amount = ask_question_int("Ange nytt antal: ");
  items[index].amount = new_amount;
}

// Lägger till objekt i databasen
void add_item_to_db(item_t *db, int *db_size, int buf_size) {
  item_t new_item = input_item();
  print_item(&new_item);
  char user_choice = toupper(ask_question_menu("Vill du lägga till varan? [J]a, [N]ej, [R]edigera\n\n", "JNR"));
 
  // Om [J]a ökar storleken på databasen och objektet sparas sist
  if (user_choice == 'J' && *db_size < buf_size) {
    save_item(db, db_size, new_item);
  }
  // Om [N]ej avbryts funktionen
  else if (user_choice == 'N') {
    return;
  }
  else {
    char *menu = "[B]eskrivning\n"\
                 "[P]ris\n"\
                 "[L]agerhylla\n"\
                 "An[t]al\n"\
                 "Välj rad eller [a]vbryt: _\n";
    
    user_choice = toupper(ask_question_menu(menu, "BPLTA"));

    switch (user_choice) {
      case 'B': {edit_description(db, *db_size-1);          break;}
      case 'P': {edit_price(db, *db_size-1);                break;}
      case 'L': {edit_shelf(db, *db_size-1);                break;}
      case 'T': {printf("Inte implementerad\n");            break;}
      case 'A': {printf("Inget lades till i databasen\n"); return;}
    }
    save_item(db, db_size, new_item);
  }
}

// Hjälpfunktion för add_item_to_db, Sparar slutgiltigt en vara i databasen
void save_item(item_t *db, int *db_size, item_t item) {
  db[*db_size] = item;
  ++(*db_size);
}

// Tar bort ett objekt från databasen
void remove_item_from_db(item_t *db, int *db_size) {
  list_db(db, *db_size);
  if (*db_size == 0) {
    printf("Inga objekt i databasen!\n");
    return;
  }
  int num;  // Index för varan att ta bort
  do {
    num = ask_question_int("Ange index för varan du vill ta bort\n");
  } while (num < 1 || num >  *db_size); //Felaktig kod! Ska vara

  for (int i = num -1; i < *db_size; ++i) {
    db[i+1] = db[i];
  }
  --(*db_size);
}

char ask_question_menu(char *menu, char *menu_choices) {
  char choice = ask_question_char(menu);

  while (!is_menu_choice(choice, menu_choices)) {
     print_menu(menu);
     choice = ask_question_char(menu);
  }
  return choice;
}

// Kontrollfunktion för ask_question_menu
bool is_menu_choice(char c, char *menu_choices) {
  char s = toupper(c);
  for (int i = 0; i < strlen(menu_choices); ++i) {
    if (s == menu_choices[i]) {
      return true;
    }
  } 
  return false;
}

void print_menu(char *menu) {
  printf("%s", menu);
}

void undo_last_action(action_t *last_action, item_t *db, int *db_size) {
  if (last_action->type == NOTHING) {
    printf("Det finns inget att ångra!\n");
    return;
  }
  else {
    pair_t items = last_action->p;
    switch (last_action->type) {
      case NOTHING : {printf("Det finns inget att ångra!\n");        break;}
      case ADD: { --(*db_size);                                      break;}
      case EDIT: {
        *items.edited = items.original;
        break;
      }
      case REMOVE: {}
    }
    last_action->type = NOTHING;  
  }T
}
