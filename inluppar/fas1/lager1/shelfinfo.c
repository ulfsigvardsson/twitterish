#include "shelfinfo.h"

struct shelf_info {
  bool exists;
  enum owner owner;
  char *item_name; // Namnet på varan vi vil lagra på ""id""
  char *shelf; // Hyllan vi vill lägga till
};


shelf_info_t *shelf_info_new() {
  shelf_info_t *new = calloc(1, sizeof(shelf_info_t));
  new->exists = false;
  new->owner = NONE;
  return new;
}
char *info_name(shelf_info_t *info) {
  return info->item_name;
}

bool info_exists(shelf_info_t *info) {
  return info->exists;
}

char* info_shelf(shelf_info_t *info) {
  return info->shelf;
}

enum owner info_owner(shelf_info_t *info) {
  return info->owner;
}

void set_info_exist(bool val, shelf_info_t *info) {
  info->exists = val;
}

void set_info_owner(shelf_info_t *info, enum owner owner) {
  info->owner = owner;
}

void set_info_name(shelf_info_t *info, char *name) {
  info->item_name = name;
}

void set_info_shelf(shelf_info_t *info, char *shelf) {
  info->shelf = shelf;
}
