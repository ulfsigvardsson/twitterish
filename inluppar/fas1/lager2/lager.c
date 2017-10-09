#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "common.h"
#include "list.h"
#include "tree.h"
#include "item.h"

#define MainMenuChoice toupper(ask_question_menu("Ange ett menyval: ", "LTRGHA"))
#define AskName ask_question_string("Ange namn: ")
#define AskDescription ask_question_string("\nAnge beskrivning: ")
#define AskPrice ask_question_int("\nAnge pris: ")
#define AskAmount ask_question_int("Välj antal att lagra: ")
#define ConfirmAddition ask_question_menu("Vill du lägga till varan? [J]a, [N]ej, [R]edigera", "JjNnRr")

typedef enum last_action {NOTHING, ADD, REMOVE, EDIT} last_action_t;

typedef struct undo_action
{
  elem_t new;
  elem_t old;
  last_action_t last_action;
} undo_action_t;

void undo_free(undo_action_t *undo)
{
  item_free(undo->new);
  item_free(undo->old);
  free(undo);
}
undo_action_t *undo_new()
{
  undo_action_t *undo = calloc(1, sizeof(undo_action_t));
  elem_t o = { .p = NULL};
  elem_t n = { .p = NULL};
  undo->new = n;
  undo->old = o; 
  undo->last_action = NOTHING;
  return undo;
}

void key_free(elem_t elem)
{
  char *key = elem.p;
  free(key);
}

void print_main_menu()
{
  printf( "\n[L]ägga till en vara\n"                            \
          "[T]a bort en vara\n"                                  \
          "[R]edigera en vara\n"                                 \
          "Ån[g]ra senaste ändringen\n"                          \
          "Lista [h]ela varukatalogen\n"                         \
          "[A]vsluta\n\n"); 
}

// list_apply-funktion. Skriver ut en enskild hylla.
bool print_shelf(elem_t elem, void *data)
{
  printf("%s  \t %d\n", shelf_id(elem.p), shelf_amount(elem.p));
  return true;
}

// Hjälpfunktion till print_item(). Skriver ut alla hyllor
void print_shelves(list_t *list)
{
  printf("Hylla \t Antal\n");
  list_apply(list, print_shelf, NULL);
}

// Skriver ut all info om en vara på skärmen
void print_item(elem_t elem)
{
  item_t *item = elem.p;
  
  printf("\n=====VARUSPECIFIKATION====\n"       \
         "Namn: %s\n"\
         "Beskrivning: %s\n"\
         "Pris: %d\n",
         item_name(item), item_descr(item), item_price(item));
  print_shelves(item_shelves(item));
}

void edit_item()
{
  return;
}

char *find_free_shelf(tree_t *db)
{
  return ask_question_shelf("Välj en ny hylla: ");
}

void db_remove_item(tree_t *db, undo_action_t *undo)
{
  return;
}

void add_existing_item(tree_t *db, elem_t name)
{
  elem_t item;
  tree_get(db, name, &item);
  list_t *shelves = item_shelves((item_t*)item.p);
  printf("Varan finns redan i databasen.\n");
  print_item(item);
  char *id = find_free_shelf(db);
  int amount = AskAmount;
  elem_t shelf = { .p = shelf_new(id, amount) };
  list_append(shelves, shelf);

}


void db_add_item(tree_t *db, undo_action_t *undo)
{
  elem_t name = {.p = AskName };
  
  // Om varan redan finns i databasen
  if (tree_has_key(db, name))
    {
      add_existing_item(db, name);
    }
  
  // Om varan inte redan finns gör vi en ny vara
  else
    {        
      char *descr  = AskDescription;
      int price    = AskPrice;
      char *new_id = find_free_shelf(db);
      int amount   = AskAmount;
      elem_t item = { .p = item_new((char*)name.p, descr, price, new_id, amount)};
      char answer = ConfirmAddition;

      switch (answer)
        {
        case 'J': {
          tree_insert(db, name, item);      
          return;
        }
        case 'N': {
          return;
        }
        default:
          tree_insert(db, name, item);
          edit_item(db, item, undo);
          return;
        }
    }
}

void edit_db(tree_t *db, undo_action_t *undo)
{
  return;
}

void undo_last_action(tree_t *db, undo_action_t *undo)
{
  return;
}

void list_20_items(int *counter, int size, tree_key_t *keys)
{
  for (int i = 0; i < 20 && *counter < size; ++i)
    {
      printf("%d: %s\n", i+1, (char*)keys[i].p);
      ++*counter;
    }
  printf("\n");
}

void list_db(tree_t *db)
{
  
  printf("=====DATABAS====\n");
  if (tree_size(db) == 0)
    {
      printf("Tom databas!\n");
      return;
    }
  
  else
    {
      tree_key_t *keys = tree_keys(db);
      int size = tree_size(db);
      int counter = 0;
      char answer;

      while (counter < size)
        {
          list_20_items(&counter, size, keys); 

          if (counter < size)
            {
              answer = ask_question_menu("Vill du se fler varor? [J]a, [N]ej", "JjNn");
              if (answer == 'J') 
                continue; 
              else 
                break; 
            }
        }
    
    }
}

// Konverterar ett intervall av heltal till en sträng och lägger till 'a' samt 'A' i slutet av den.
// Strängen används för att välja ett intervall av index i menyn.
char *index_menu_choices(int item_count)
{
  int index = 1+'0'; //Heltals-motsvarigheten till '1'
  char menu_choices[item_count+2]; // Char-array för alla index med två extra platser för 'A' och 'a'
  for (int i = 0; i < item_count; ++i)
    {
      menu_choices[i] = index+i; // ASCI-motsvarigheten till 'i'
    }
  menu_choices[item_count] = 'a';
  menu_choices[item_count+1] = 'A';
  return strdup(menu_choices);
}

// Låter användaren välja en vara i listan efter index
elem_t select_by_index(tree_t *db, int item_count)
{
  char *menu_choices = index_menu_choices(item_count);
  char answer = ask_question_menu("Välj index eller [a]vbryt: ", menu_choices); 
  elem_t result = { .p = NULL };
  
  if (answer == 'A' || answer == 'a') return result; 
  else
    {
      int index = atoi(&answer); // Konvertera valet till ett heltal
      elem_t *elems = tree_elements(db);
      result = elems[index-1]; 
    }
  free(menu_choices);
  return result;
}

void list_and_select_item(tree_t *db)
{
  
  list_db(db);
  if (tree_size(db) != 0)
    {
    
      elem_t item = select_by_index(db, tree_size(db));
      if (item.p)
        {
          print_item(item); 
        }
    }
}

void event_loop(tree_t *db)
{
  undo_action_t *undo = undo_new();
  char choice;
  
  do
    {
      print_main_menu();
      
      choice = MainMenuChoice;

      switch (choice) {

      case 'L': {db_add_item(db, undo);         break;}
      case 'T': {db_remove_item(db, undo);      break;}
      case 'R': {edit_db(db, undo);             break;}
      case 'G': {undo_last_action(db, undo);    break;}
      case 'H': {list_and_select_item(db);      break;}
      default:  printf("Avslutar...\n");        break;}
    } while (choice != 'A');
  
  undo_free(undo); 
}

int main(int argc, char *argv[])
{
  tree_t *db = tree_new(item_copy, key_free, item_free, item_compare);
  event_loop(db);
  tree_delete(db, true, true);
  return 0;
}
