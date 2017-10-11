#include "shelfinfo.h"

struct shelf_info {
  bool exists;
  enum owner owner;
  char *name;
  char *id;
};

shelf_info_t *shelf_info_new() {
  shelf_info_t *new = calloc(1, sizeof(shelf_info_t));
  return new;
}

shelf_info_t *info_initiate(void) {
  shelf_info_t *info = shelf_info_new();
  set_info_exists(false, info);
  set_info_owner(NONE, info);
  set_info_name(NULL, info);
  set_info_id(NULL, info);
  return info;
}

bool info_exists(shelf_info_t *info) {
  return info->exists;
}

enum owner info_owner(shelf_info_t *info) {
  return info->owner;
}

char *info_name(shelf_info_t *info) {
  return info->name;
}

char *info_id(shelf_info_t *info) {
  return info->id;
}

void set_info_exists(bool val, shelf_info_t *info) {
  info->exists = val;
}

void set_info_owner(enum owner owner, shelf_info_t *info) {
  info->owner = owner;
}

void set_info_name(char *name, shelf_info_t *info) {
  info->name = name;
}

void set_info_id(char *id, shelf_info_t *info) {
  info->id = id;
}
