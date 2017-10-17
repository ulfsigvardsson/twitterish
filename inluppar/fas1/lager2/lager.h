#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shelfinfo.h"
#include "utils.h"
#include "common.h"
#include "list.h"
#include "tree.h"
#include "item.h"

typedef enum last_action {NOTHING, ADD, REMOVE, EDIT} last_action_t;

typedef struct undo_action
{
  elem_t added;
  elem_t removed;
  elem_t edit_old;
  elem_t edit_new;
  last_action_t last_action;
} undo_action_t;

/// Skapar en ny undo-strukt
undo_action_t *undo_new();

/// Återställer undo strukten till default-värden mellan varven
///
/// \param undo undo-strukten som ska återställas
void undo_reset(undo_action_t *undo);

/// Free-funktion för undo_action-strukten
/// Om sista aktionen var att ta bort en vara är undo->new == NULL
/// och ska därmed INTE frigöras
/// \param undo undo-strukten
void undo_free(undo_action_t *undo);

/// Skriver ut huvudmenyn
void print_main_menu();

/// list_apply-funktion. Skriver ut en enskild hylla.
///
/// \elem elementet som innehåller hyllan
/// \data parameter för att uppfylla specifikationen för list_apply
bool print_shelf(elem_t elem, void *data);

/// Hjälpfunktion till print_item(). Skriver ut alla hyllor
///
/// \list listan med hyllor
void print_shelves(list_t *list);


/// Skriver ut all info om en vara på skärmen
/// param elem varan att skriva ut
///
/// \param elem elementet innehållande item
void print_item(elem_t elem);


/// Låter användaren välja en av hyllorna för en vara
///
/// \param item en vara att editera
/// \param result elem_t-pekare att lagra vald hylla i
/// \returns index på vald hylla i listan
int select_existing_shelf(elem_t item, elem_t *result);

/// HJälpfunktion för shelf_is_in_list
///
/// \param shelf hyllan att jämföra med
/// \param info HI-strukt som innehåller hyllnamnet vi söker efter
bool shelf_is_equal(elem_t shelf, void *info);


/// HJälpfunktion för find_available_shelf. Söker igenom en lista av hyllor efter
/// ett specifikt hyllnamn.
///
/// \param key namnet på varan vars hyllor vi söker igenom
/// \param item ett item som innehåller hyllistan
/// \info HI-strukt som sparar ägarinformation om hyllan.
/// \returns true om hyllan finns i listan, annars false
bool shelf_is_in_list(elem_t key, elem_t item, void *info);


void merge_shelves(shelf_info_t *info, elem_t shelf_to_edit, list_t *shelves);

/// Söker igenom databasen efter hyllnamn som användaren anger.
/// Returnerar ett hyllnamn som inte är upptaget av en annan vara än den aktuella.
///
/// \param tree databasen
/// \param name hyllnamnet som trädet söks mot
/// \param info en strukt som innehåller ägandeförållanden om hyllan
/// \returns namnet på den tillgängliga hyllan
char *find_available_shelf(tree_t *db, char *name, shelf_info_t *info);


/// Avänds vid redigering av lagerhylla när två hyllor ska slås ihop
///
/// \param info info strukten för hyllan som ska merge:a
/// \param shelf_to_edit den gamla hyllan
/// \param shelves listan med alla hyllor 
void merge_shelves(shelf_info_t *info, elem_t shelf_to_edit, list_t *shelves);


/// Redigerar namn på en varas hylla
///
/// \param db lagret
/// \param shelf_to_edit hyllan som ska redigeras
/// \param name det nya namnet på hyllan
/// \param shelves listan med hyllorna
void edit_shelf_name(tree_t * db, elem_t shelf_to_edit, char *name, list_t *shelves);


/// Redigerar en hylla tillhörande en vara
///
/// \param db lagret
/// \param item varan att ändra hylla på
/// \param edit_choice signalerar den ändring som ska göras
void edit_shelves(tree_t *db, elem_t item, char edit_choice);


/// Redigerar beskrivningen på en vara
/// \param item varan att ändra beskrivningen på
void edit_description(item_t *item);


/// Redigerar priset på en vara
/// \param item varan att ändra namnet på
void edit_name(item_t *item);


/// Redigerar en vara i databasen
/// \param tree databasen
/// \param item varan som ska redigeras
/// \param undo strukt för att ångra
/// \param edit_choice signalerar vilken del av varan som ska redigeras
void edit_item_aux(tree_t *db, elem_t item, undo_action_t *undo, char edit_choice);


/// Frigör alla hyllor i en lista
///
/// \param shelves lista med alla hyllor
void remove_shelves(list_t *shelves);

/// Tar bort en vara från databasen.
///
/// \param db lagret
/// \param undo undo strukten som sparas ifall man vill ångra
void db_remove_item(tree_t *db, undo_action_t *undo);


/// Lägger till en antal av en redan existerande vara i databasen
///
/// \param db lagret
/// \param name namnet på varan som ska
void add_existing_item(tree_t *db, elem_t name);


/// Låter användaren mata in ett positivt nummer över 0
///
/// \returns antalet användaren matade in
int ask_new_amount();

/// Låter användaren mata in ett positivt nummer över 0
///
/// \returns antalet användaren matade in
int ask_new_price();



/// Lägger till en vara i databasen. Om varan redan finns väljer användaren
/// en hylla att lägga till på. Om hyllan redan innehåller varan läggs det nya
/// antalet till det existerande.
///
/// \param db lagret
/// \param undo undo strukten som sparar informationen ifall en ångring sker
void db_add_item(tree_t *db, undo_action_t *undo);


/// Listar 20 varor i databasen med tillhörande index
///
/// \param counter håller koll på indexeringen av varor
/// \param size antalet varor i lagret
/// \keys lista med alla keys som printas ut
void list_20_items(int *counter, int size, tree_key_t *keys);


/// Listar 20 varor åt gången tills användaren väljer en specifik vara
/// att inspektera eller avbryter
///
/// \param db lagret
/// \returns true eller false beroende på om användaren vill fortsätta till nästa 20
bool list_db(tree_t *db);


// Konverterar ett intervall av heltal till en sträng och lägger till 'a' samt 'A' i slutet av den.
/// Strängen används för att välja ett intervall av index i menyn.
///
/// \param item_count antalet index som ska finnas
/// \returns lista med intar innehållande antalet valida svar (får konverteras till char sedan)
int *index_menu_choices(int item_count);


/// Kollar att en given index är valid
///
/// \param valid_indexes lista med antalet valida index
/// \param array_length längden på listan med valida index
/// \param index index som användaren matar in
/// \returns true eller false beroende på om index är valid eller inte
bool valid_index(int *valid_indexes, int array_length, int index);


/// Låter användaren välja en vara i listan efter index eller avbryta och återgå
/// till huvudmeny
///
/// \param db lagret
/// \param item count antalet
/// \returns det item som blev valt
elem_t select_by_index(tree_t *db, int item_count);


/// Listar databasens varor med index på formen
///
/// 1. vara1
/// 2. vara2
/// .
/// .
/// N. varaN
/// \param db lagret
void list_and_select_item(tree_t *db);


/// Används för att redigera en vara
///
/// \param db lagret
/// \param item den vara som ska redigeras
/// \param undo undo strukten som ska sparar information ifall en ångring sker
void edit_item(tree_t *db, elem_t item, undo_action_t *undo);


/// Huvudfunktion för att redigera en vara i databasen
///
/// \param db lagret
/// \param undo undo strukten
void edit_db(tree_t *db, undo_action_t *undo);


/// Returnerar antalet poster i databasfilen
///
/// \param f filen som ska läsas
/// \returns antalet poster i databasfilen
int db_size(FILE *f);



/// Sparar en post i lagret till en fil
///
/// \param key nyckeln till posten
/// \param elem den vara som ska sparas
/// \param f path till filen
/// \returns true om operationen lyckas, false om inte
bool write_item_to_file(tree_key_t key, elem_t elem,  void *f);


/// Sparar hela lagret till en fil
///
/// \param db lagret
/// \param path sökvägen till filen
void save_db(tree_t *db, char *path);


/// Laddar in databasen till programmet
///
/// \param path sökvägen till filen
/// \returns ett träd innehållande alla poster från filen
tree_t *load_db(char *path);


/// Huvudloop för programmet
///
///param path sökvägen till filen innehållande sparad databas
void event_loop(char *path);















  
