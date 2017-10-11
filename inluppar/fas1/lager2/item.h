#ifndef ITEM_H
#define ITEM_H
#include "list.h"
#include "common.h"

typedef struct item item_t;

// shelf is a struct included in item_t
typedef struct shelf shelf_t;


/// Allokerar plats för en ny vara och sätter dess information
/// \param name: namn på varan
/// \param descr: beskrivning på varan
/// \param price: pris på varan
/// \param shelf_id: hyllplatsen på formen xy där x är en versal och y ett heltal
/// \param amount: antalet varor av denna typ
item_t *item_new(char *name, char *descr, int price, char *id, int amount);

item_t *item_empty();

/// Allokerar plats för en ny shelf_t och initierar till noll.
shelf_t *shelf_new(char *id, int amount);

void item_set_name(item_t *item, char *name);
/// Ändrar objektsbeskrivningen för ett objekt
/// \param item: objektet att editera
void item_set_description(item_t *item, char *descr);

/// Ändrar priset för ett objekt
/// \param item: objektet att editera
void item_set_price(item_t *item, int price);

/// Ändrar hyllplats för ett objekt
/// \param item: objektet att editera
void item_set_shelf(shelf_t *shelf, char *id);

/// Ändrar antalet för ett objekt
/// \param item: objektet att editera
void item_set_amount(shelf_t *shelf, int amount);

void shelf_add_amount(shelf_t *shelf, int amount);
void item_set_shelves(item_t *item, list_t *shelves);

/// Returnerar namnet på ett item
/// \param item: objektet att returnera namnet för
char *item_name(item_t *item);

/// Returnerar beskrivningen på ett item
/// \param item: objektet att returnera beskrivningen för
char *item_descr(item_t *item);

/// Returnerar priset på ett item
/// \param item: objektet att returnera priset för
int item_price(item_t *item);

/// Returnerar en lista av hyllor där en vara finns
/// \param item: varan att lista hyllplatser för
list_t *item_shelves(item_t *item);

/// Returnerar namnet på en hylla
/// \param shelf: en shelf_t
char *shelf_id(shelf_t *shelf);

/// Returnerar antalet lagrade varor på en hylla
/// \param shelf: en shelf_t
int shelf_amount(shelf_t *shelf);

int item_compare(elem_t elem1, elem_t elem2);
elem_t item_copy(elem_t item);
void item_free(elem_t elem);
void shelf_free(elem_t elem);
void shelf_free_aux(shelf_t *shelf);
int shelf_compare(elem_t elem1, elem_t elem2);
elem_t shelf_copy(elem_t shelf);
item_t *item_deep_copy(elem_t from);

#endif
