#include "saveinfo.h"

struct save_info {
  bool exists;
  enum owner owner;
  char *name;
  char *id;
};

save_info_t *save_info_new() {
  save_info_t *new = calloc(1, sizeof(save_info_t));
  return new;
}

save_info_t *info_initiate(void) {
  save_info_t *info = save_info_new();
  set_info_exists(false, info);
  set_info_owner(NONE, info);
  set_info_name(NULL, info);
  set_info_id(NULL, info);
  return info;
}

bool info_exists(save_info_t *info) {
  return info->exists;
}

enum owner info_owner(save_info_t *info) {
  return info->owner;
}

char *info_name(save_info_t *info) {
  return info->name;
}

char *info_id(save_info_t *info) {
  return info->id;
}

void set_info_exists(bool val, save_info_t *info) {
  info->exists = val;
}

void set_info_owner(enum owner owner, save_info_t *info) {
  info->owner = owner;
}

void set_info_name(char *name, save_info_t *info) {
  info->name = name;
}

void set_info_id(char *id, save_info_t *info) {
  info->id = id;
}
