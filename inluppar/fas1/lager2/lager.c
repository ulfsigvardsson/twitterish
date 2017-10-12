#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shelfinfo.h"
#include "utils.h"
#include "common.h"
#include "list.h"
#include "tree.h"
#include "item.h"

#define MainMenuChoice toupper(ask_question_menu("Ange ett menyval: ", "KLTRGHA"))
#define AskName ask_question_string("Ange namn: ")
#define AskDescription ask_question_string("Ange beskrivning: ")
#define AskPrice ask_question_int("Ange pris: ")
#define AskShelf ask_question_shelf("Välj en hylla: ");
#define AskAmount ask_question_int("Välj antal att lagra: ")
#define ConfirmAddition ask_question_menu("\nVill du lägga till varan? [J]a, [N]ej, [R]edigera", "JjNnRr")
#define AskRemoveShelf ask_question_shelf("Välj hylla att ta bort ifrån: ")
#define ShelfIsInList list_apply(shelves, shelf_is_equal, info)
#define AskWhatToEdit ask_question_menu("\n[B]eskrivning\n"             \
                                        "[P]ris\n"                      \
                                        "[L]agerhylla\n"                \
                                        "An[t]al\n\n"                   \
                                        "Välj rad eller [a]vbryt: ", "BbPpLlTtAa");


typedef enum last_action {NOTHING, ADD, REMOVE, EDIT} last_action_t;

typedef struct undo_action
  {
    elem_t new;
    elem_t old;
    last_action_t last_action;
  } undo_action_t;

bool list_db(tree_t *db);
void list_and_select_item(tree_t *db);
elem_t select_by_index(tree_t *db, int item_count);
void edit_item(tree_t *db, elem_t item, undo_action_t *undo);

/// Återställer undo-strukten till default-värden mellan varven
void undo_reset(undo_action_t *undo)
{
  if (undo->last_action == NOTHING) return; 

  undo->last_action = NOTHING;
  item_free(undo->new);
  item_free(undo->old); 
}
/// Free-funktion för undo_action-strukten
/// Om sista aktionen var att ta bort en vara är undo->new == NULL
/// och ska därmed INTE friöras
/// TODO: Skilj på hur elementen frigörs beroende på vad som gjordes sist
void undo_free(undo_action_t *undo)
{
  if (undo->last_action == REMOVE) item_free(undo->old); 
  if (undo->last_action == EDIT)
    {
      item_free(undo->old);
      item_free(undo->new);
    }
  if (undo->last_action == ADD)
    {
      item_free(undo->new);
    }
  free(undo);
}


/// Initieringsfunktion för undo_action-strukten.
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
  // char *key = elem.p;
  //free(key);
}


/// Skriver ut huvudmenyn
void print_main_menu()
{
  printf( "\n[L]ägga till en vara\n"              \
          "[T]a bort en vara\n"                   \
          "[R]edigera en vara\n"                  \
          "Ån[g]ra senaste ändringen\n"           \
          "Lista [h]ela varukatalogen\n"          \
          "[K]ontrollera databasens sortering\n"  \
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


/// Skriver ut all info om en vara på skärmen
/// param elem varan att skriva ut
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


/// Låter användaren välja en av hyllorna för en vara
/// \param item en vara att editera
/// \param result elem_t-pekare att lagra vald hylla i
/// \returns index på vald hylla i listan
int select_existing_shelf(elem_t item, elem_t *result)
{
  list_t *shelves = item_shelves(item.p); 
  int index = 0;
  elem_t lookup;
  do
    {
       char *shelf_to_edit = AskShelf;
       lookup.p = shelf_new(shelf_to_edit, 0);
       index = list_contains(shelves, lookup);

       if (index == -1)
         {
           printf("Ogiltigt val!\n");
           shelf_free(lookup);
         }

     } while (index == -1);

   list_get(shelves, index, result);
   shelf_free(lookup);
   return index;
}

/// HJälpfunktion för shelf_is_in_list
/// \param shelf hyllan att jämföra med
/// \param info HI-strukt som innehåller hyllnamnet vi söker efter
bool shelf_is_equal(elem_t shelf, void *info)
{
  char *lookup_id = info_id(info);
  char *current_id = shelf_id(shelf.p);
  
  if (strcmp(lookup_id, current_id) == 0)
    {
      set_info_exists(true, info);
      return true;
    }
      
  else return false;
  }


/// HJälpfunktion för find_available_shelf. Söker igenom en lista av hyllor efter
/// ett specifikt hyllnamn.
/// \param key namnet på varan vars hyllor vi söker igenom
/// \param item ett item som innehåller hyllistan
/// \info HI-strukt som sparar ägarinformation om hyllan.
/// \returns true om hyllan finns i listan, annars false
bool shelf_is_in_list(elem_t key, elem_t item, void *info)
{
  list_t *shelves = item_shelves(item.p);
  char *lookup_name = info_name(info);
  char *current_name = item_name(item.p);

  if (ShelfIsInList)
    {
      set_info_exists(true, info);
      set_shelf_owner(info, current_name, lookup_name);
    }
  
  return info_exists(info);
}

/// Söker igenom databasen efter hyllnamn som användaren anger.
/// Returnerar ett hyllnamn som inte är upptaget av en annan vara än den aktuella.
char *find_available_shelf(tree_t *db, char *name, shelf_info_t *info)
{
  char *chosen_id;
  set_info_name(name, info);
  
  do
    {
      set_info_exists(false, info);
      set_info_owner(NONE, info);
      
      chosen_id = ask_question_shelf("Välj en ny hylla: ");
      set_info_id(chosen_id, info);

      tree_apply(db, preorder, shelf_is_in_list, info); 

      if (info_owner(info) == OTHER)
        {
          printf("Hyllan är upptagen!\n");
          free(chosen_id);  
        }
    }  while (info_owner(info) == OTHER);

  return chosen_id; 
}


void edit_shelf_name(tree_t * db, elem_t shelf_to_edit, char *name)
{
  shelf_info_t *info = info_initiate();
  char *new_id = find_available_shelf(db, name, info);
  
  char *tmp = shelf_id(shelf_to_edit.p);
  set_shelf_id(shelf_to_edit.p, new_id);
  free(info);
  free(tmp); 
}


void edit_shelves(tree_t *db, elem_t item, char edit_choice, undo_action_t *undo)
{
  print_shelves(item_shelves(item.p));
  
  elem_t shelf_to_edit;
  int index = select_existing_shelf(item, &shelf_to_edit);
  char *name = item_name(item.p);
  
  if (edit_choice == 'L')
    {
      edit_shelf_name(db, shelf_to_edit, name);
    }
  else
    {
      int new_amount = AskAmount;
      shelf_set_amount(shelf_to_edit.p, new_amount);
    }
}


/// Redigerar beskrivningen på en vara
void edit_description(item_t *item)
{  
  printf("Nuvarande beskrivning: %s\n"                                  \
         "-----------------------------------------------------\n", item_descr(item));
  char *new_descr = ask_question_string("Ny beskrivning: ");
  item_set_description(item, new_descr); 
}


/// Redigerar priset på en vara
void edit_price(item_t *item)
{  
  printf("Nuvarande pris: %d\n"                                         \
         "-----------------------------------------------------\n", item_price(item));
  int new_price = ask_question_int("Nytt pris: ");
  item_set_price(item, new_price); 
}


/// Redigerar en vara i databasen
/// \param tree: databasen
/// \param item: varan som ska redigeras
/// \param undo: strukt för att ångra
void edit_item_aux(tree_t *db, elem_t item, undo_action_t *undo, char edit_choice)
{  
  
  switch (edit_choice)
    {
    case 'P':
      {
        edit_price(item.p);
        break;
      }
    case 'B':
      {
        edit_description(item.p);
        break;
      }
    default :
      {
        edit_shelves(db, item, edit_choice, undo);
      }
    }
}


//TODO: lägg till logik för att hitta en ledig hylla
char *find_free_shelf(tree_t *db)
{
  return ask_question_shelf("Välj en ny hylla: ");
}


void remove_shelves(list_t *shelves)
{
  print_shelves(shelves); 
  int index_to_remove = -1; // list_contains returnerar -1 om hyllan inte finns i listan
  
  do
    {
      //TODO: läs in ett hyllnamn och plocka ut hyllan
      // från listan. Måste kanske skapa en list_apply-funktion för att hitta den. 
      elem_t shelf_to_remove = { .p = shelf_new(AskRemoveShelf, 0) };
      index_to_remove = list_contains(shelves, shelf_to_remove);
      
      if (index_to_remove == -1) printf("Ogiltigt val!\n");
      shelf_free(shelf_to_remove);
      
    } while (index_to_remove == -1);

  list_remove(shelves, index_to_remove, true);
}


/// Tar bort en vara från databasen.
void db_remove_item(tree_t *db, undo_action_t *undo)
{
  if(!list_db(db)) return;

  //Välj vilken vara som ska tas bort
  elem_t item = select_by_index(db, tree_size(db));

  // select_by_index returnerar en nullpekare om man avbryter
  if (item.p)
    {
      // Hittils räknas handlingen som att vi editerar en hylla
      undo_reset(undo);
      undo->last_action = EDIT;
      undo->old.p = item_deep_copy(item);

      elem_t key = { .p = item_name(item.p) };
      elem_t result;

      tree_get(db, key, &result); 
      list_t *shelves = item_shelves(result.p);
      remove_shelves(shelves);

      if (list_length(shelves) == 0)
        {
          // Är det den sista hyllan som tas bort blir det en borttagning av vara
          undo_reset(undo);
          undo->last_action = REMOVE;
          tree_remove(db, key, &result); 
          item_free(item);
        }
    }
}


/// Lägger till en antal av en redan existerande vara i databasen
void add_existing_item(tree_t *db, elem_t name)
{
  elem_t item;
  tree_get(db, name, &item);
  list_t *shelves = item_shelves((item_t*)item.p);

  printf("Varan finns redan i databasen.\n");
  print_item(item); 

  shelf_info_t *info = info_initiate(); 
  char * id          = find_available_shelf(db, name.p, info); 
  int amount         = AskAmount;

  // Varan finns redan på vald hylla
  if (info_owner(info) == SELF)
    {
      elem_t target_shelf;
      elem_t temp = { .p = shelf_new(id, amount) };
      int index = list_contains(shelves, temp);
      list_get(shelves, index, &target_shelf);
      shelf_add_amount(target_shelf.p, amount);
      shelf_free(temp);
    }
  // Hyllan är ledig
  else
    {
      elem_t shelf  = { .p = shelf_new(id, amount) };
      list_append(shelves, shelf); 
    }
  free(info);
}


/// Lägger till en vara i databasen. Om varan redan finns väljer användaren
/// en hylla att lägga till på. Om hyllan redan innehåller varan läggs det nya
/// antalet till det existerande.
void db_add_item(tree_t *db, undo_action_t *undo)
{
  printf("\n=====NY VARA====\n");
  elem_t name = {.p = AskName };
  
  // Om varan redan finns i databasen
  if (tree_has_key(db, name))
    {
      elem_t item;
      tree_get(db, name, &item);

      undo_reset(undo);
      undo->last_action = EDIT;
      undo->old.p = item_deep_copy(item); 
      add_existing_item(db, name); 
      undo->new.p = item_deep_copy(item);
      free(name.p);
    }
  // Om varan inte redan finns gör vi en ny vara
  else
    {
      shelf_info_t *info = info_initiate();
      char *descr  = AskDescription;
      int price    = AskPrice; 
      char *new_id = find_available_shelf(db, name.p, info); 
      int amount   = AskAmount;
      elem_t item = { .p = item_new((char*)name.p, descr, price, new_id, amount)};
      print_item(item);
      char answer = ConfirmAddition;

      switch (answer)
        {
        case 'N':
          {
            item_free(item);
            break;
          }
        case 'J':
          {
            undo_reset(undo);
            undo->last_action = ADD; 
            tree_insert(db, name, item);
            undo->new.p = item_deep_copy(item);
            break;
          }

        default:            
          tree_insert(db, name, item);
          edit_item(db, item, undo);
          undo->last_action = ADD;
          break;
        }
      free(info);
    }
}


/// Ångrar den senaste handlingen
void undo_last_action(tree_t *db, undo_action_t *undo)
{
  switch (undo->last_action)
    {
    case NOTHING:
      {
        printf("Inget att ångra. \n");
        return;
      }
    case ADD:
      {
        elem_t result;
        elem_t key = { .p = item_name(undo->new.p) };
        
        tree_remove(db, key, &result);
        item_free(result);
        item_free(undo->new);
        break;
      }
    case REMOVE:
      {
        elem_t key  = { .p = item_name(undo->old.p) };
        elem_t elem = { .p = undo->old.p };
        
        tree_insert(db, key, elem); 
        break;
      }
    case EDIT:
      {
        elem_t key  = { .p = item_name(undo->old.p)};
        elem_t item_to_undo;
        tree_remove(db, key, &item_to_undo);
        item_free(item_to_undo);
        elem_t reset = {.p = item_deep_copy(undo->old)};
        tree_insert(db, key, reset); 
        break;
      }
    default:
      break;
    }
  undo_reset(undo);
}


/// Listar 20 varor i databasen med tillhörande index
void list_20_items(int *counter, int size, tree_key_t *keys)
{
  for (int i = 0; i < 20 && *counter < size; ++i)
    {
      printf("%d: %s\n", i+1, (char*)keys[i].p);
      ++*counter;
    }
  printf("\n");
}


/// Listar 20 varor åt gången tills användaren väljer en specifik vara
/// att inspektera eller avbryter
bool list_db(tree_t *db)
{
  
  printf("=====DATABAS====\n");
  if (tree_size(db) == 0)
    {
      printf("Tom databas!\n");
      return false;
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

              if (answer == 'J') continue; 
              else break; 
            }
        }
      free(keys);
      return true;
    }
}


// Konverterar ett intervall av heltal till en sträng och lägger till 'a' samt 'A' i slutet av den.
/// Strängen används för att välja ett intervall av index i menyn.
char *index_menu_choices(int item_count)
{
  int index = 1+'0';               //Heltals-motsvarigheten till '1'
  char menu_choices[item_count+2]; // Char-array för alla index med två extra platser för 'A' och 'a'

  for (int i = 0; i < item_count; ++i)
    {
      menu_choices[i] = index+i;   // ASCI-motsvarigheten till 'i'
    }
  
  menu_choices[item_count]   = 'a';
  menu_choices[item_count+1] = 'A';
  return strdup(menu_choices);
}



/// Låter användaren välja en vara i listan efter index eller avbryta och återgå
/// till huvudmenyn
elem_t select_by_index(tree_t *db, int item_count)
{
  char *menu_choices = index_menu_choices(item_count);
  char answer   = ask_question_menu("Välj index eller [a]vbryt: ", menu_choices); 
  elem_t result = { .p = NULL }; 
  
  if (answer != 'A' && answer != 'a')
    {
      int index = atoi(&answer); // Konvertera valet till ett heltal
      elem_t *elems = tree_elements(db);
      result = elems[index-1];
      free(elems);
    }

  free(menu_choices); 
  return result;  
}

/// Listar databasens varor med index på formen
///
/// 1. vara1
/// 2. vara2
/// .
/// .
/// N. varaN
void list_and_select_item(tree_t *db)
{
  list_db(db);
  if (tree_size(db) != 0)
    {
      elem_t item = select_by_index(db, tree_size(db));
      if (item.p) print_item(item); 
    }
}

void edit_item(tree_t *db, elem_t item, undo_action_t *undo)
{
  print_item(item);
  char edit_choice = AskWhatToEdit;

  if (edit_choice == 'A') return;
      
  else
    {
      undo_reset(undo);
      undo->last_action = EDIT;
      undo->old.p = item_deep_copy(item);
      edit_item_aux(db, item, undo, edit_choice);
      undo->new.p = item_deep_copy(item);
    }
}

/// Huvudfunktion för att redigera en vara i databasen
void edit_db(tree_t *db, undo_action_t *undo)
{
  if (!list_db(db)) return;
  
  undo->last_action = EDIT;
  elem_t item = select_by_index(db, tree_size(db));
  
  if (item.p)
    {
      edit_item(db, item, undo); 
    }
}

void db_check_sorting(tree_t *db)
{
  return;
}
/// Huvudloop för programmet. 
void event_loop(tree_t *db)
{
  char choice;
  undo_action_t *undo = undo_new();
  do
    {
      print_main_menu();
      
      choice = MainMenuChoice;

      switch (choice)
        {
        case 'L': {db_add_item(db, undo);         break;}
        case 'T': {db_remove_item(db, undo);      break;}
        case 'R': {edit_db(db, undo);             break;}
        case 'G': {undo_last_action(db, undo);    break;}
        case 'H': {list_and_select_item(db);      break;}
        case 'K': {db_check_sorting(db);          break;}
        default:  printf("Avslutar...\n");        break;}
      
    } while (choice != 'A');
  
   undo_free(undo); 
}


int main(int argc, char *argv[])
{
  tree_t *db = tree_new(item_copy, NULL, item_free, item_compare);
  
  event_loop(db);
  tree_delete(db, false, true);
  return 0;
}
