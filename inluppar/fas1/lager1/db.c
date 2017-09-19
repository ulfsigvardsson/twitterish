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
#include "list.h"



//====PROTOTYPES====

void print_item(item_t *item);
bool is_menu_choice(char c, char *menu_choices);
void print_menu();
bool is_valid_shelf(char *str);
int add_to_string(char *arr[], char *buf, int index);
shelf_t to_shelf(char *shelf);
void edit_description(item_t *item);
void edit_price(item_t *item);
void edit_description(item_t *item);
void edit_shelf(item_t *item);
void save_item(tree_t *db, item_t *item);


//====FUNCTIONS====

// Skriver ut en enskild vara
void print_item(item_t *item) {
  int kronor = (item->price)/100;
  int oren   = (item->price)%100;
  
  printf("\n=====VARUSPECIFIKATION=====\n");
  printf("Namn: %s\n", item->name);
  printf("Beskrivning: %s\n", item->descr);
  printf("Pris: %d.%d SEK\n", kronor, oren);
  printf("Här skrivs hyllor och antal ut\n");
}

shelf_t make_shelf(char *shelf_id, int amount) { // Osäker på om jag behöver allokera denna
  shelf_t s = { .id = shelf_id, .amount = amount };
  return s;
}

// Skapar en vara
item_t *make_item(char *name, char *descr, int price) {
  item_t *item = calloc(1, sizeof(item_t));
  item->name   = name;
  item->descr  = descr;
  item->price  = price;
  return item;
}

// Låter användaren mata in information om en vara och skapar en ny vara
item_t *input_item() {
  char *name       = ask_question_string("Ange namn på vara: ");
  char *descr      = ask_question_string("\nAnge en beskrivning av varan: ");
  int price        = ask_question_int("\nAnge pris på varan :");
  return make_item(name, descr, price);
}


// Hjälpfunktion för edit_db, ändrar på objektsbeskrivningen
void edit_description(item_t *item) {
  return;
}

// Hjälpfunktion för edit_db, ändrar på priset
void edit_price(item_t *item) {
  return;
}

// Hjälpfunktion för edit_db, ändrar på hyllan
void edit_shelf(item_t *item) {
  return;
}

// Hjälpfunktion för edit_db, ändrar på antalet objekt
void edit_amount(item_t *item) {
  return;
}


// Kontrollfunktion för ask_question_menu
bool is_menu_choice(char c, char *menu_choices) {
  return false;
}

void print_menu(char *menu) {
  printf("%s", menu);
}

void undo_last_action(action_t *last_action, tree_t *db) {

}
