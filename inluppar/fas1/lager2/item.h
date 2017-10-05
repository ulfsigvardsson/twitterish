#ifndef ITEM_H
#define ITEM_H
#include "list.h"
#include "common.h"

//! \brief Typedef för lagervaru-strukten
typedef struct item item_t;

//! \brief Typedef för hyll-strukten
typedef struct shelf shelf_t;


/// Allokerar plats på heapen för en ny vara och sätter dess information enligt parametrar
/// \param name namn på varan
/// \param descr beskrivning på varan
/// \param price pris på varan
/// \param shelf_id hyllplatsen på formen xy där x är en versal och y ett heltal
/// \param amount antalet varor av denna typ
/// \returns pekare til den nya varan
item_t *item_new(char *name, char *descr, int price, char *shelf_id, int amount);

item_t *item_empty();

//! Skapar en ny hylla
/*!
 * Allokerar plats för en ny hylla på heapen med id och antal varor enligt parametrar.
 * \param id Hyllans id
 * \param amount Antal varor att lagra på hyllan
 * \returns pekare till den nya hyllan 
 */
shelf_t *shelf_new(char *id, int amount);

//! Ändrar namnet för ett vara
/*! \param item varan att editera
 *  \param descr ny beskrivning på varan
 */
void item_set_name(item_t *item, char *name);

//! Ändrar varasbeskrivningen för ett vara
/*! \param item varan att editera
 *  \param descr ny beskrivning på varan
 */
void item_set_description(item_t *item, char *descr);

//! Ändrar priset för en vara
/*! \param ite: varan att editera
 *  \param price nytt pris på varan
 */
void item_set_price(item_t *item, int price);

//! Ändrar hyllplats för en vara
/*! \param item varan att editera
 *  \param id det nya hyllnamnet för varan
 */
void item_set_shelf(shelf_t *shelf, char *id);

//! Ändrar antalet lagrade varor av en viss typ
/*! \param item varan att editera
 *  \param amount det nya antalet varor 
 */ 
void item_set_amount(shelf_t *shelf, int amount);

//! Ändrar en varas lista av hyllor
/*! \param item varan att editera
  \param shelves den nya listan av hyllor
*/
void item_set_shelves(item_t *item, list_t *shelves);

//! Returnerar namnet på en vara
/*! \param item varan att returnera namnet för
 *  \returns varans namn
 */
char *item_name(item_t *item);

//! Returnerar beskrivningen på en vara
/*! \param item varan att returnera beskrivningen för
 *  \returns varans beskrivning 
 */
char *item_descr(item_t *item);

//! Returnerar priset på ett item
/*! \param item varan att returnera priset för
 *  \returns varans pris 
 */
int item_price(item_t *item);

//! Returnerar en lista av hyllor där en vara finns
/*! \param item varan att lista hyllplatser för
 *  \returns en lista av varans hyllor 
 */
list_t *item_shelves(item_t *item);

//! Returnerar namnet på en hylla
/*! \param shelf hyllan att returnera namnet på
 *  \returns hyllans namn
 */
char *shelf_id(shelf_t *shelf);

//! Returnerar antalet lagrade varor på en hylla
/*! \param shelf hyllan för vilken att returnera antalet varor 
 *  \returns antal varor på hyllan
 */
int shelf_amount(shelf_t *shelf);

//! Kopierar en varas information till en annan
/*! \param original varan att kopiera från
 *  \param copy varan att kopiera till
 */
void item_copy(item_t *original, item_t *copy);

//! Kopierar en varas hyllista till en annan
/*! \param original varan att kopiera från
 *  \param copy varan att kopiera till
 */
void shelf_copy(item_t *original, item_t *copy);

#endif
