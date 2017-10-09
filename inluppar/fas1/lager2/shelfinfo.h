#include <stdlib.h>
#include <stdbool.h>

enum owner {OTHER, NONE, SELF};


typedef struct shelf_info shelf_info_t;

shelf_info_t *shelf_info_new();

bool info_exists(shelf_info_t *info);

enum owner info_owner(shelf_info_t *info);

char *info_name(shelf_info_t *info);

char *info_id(shelf_info_t *info);

void set_info_exists(bool val, shelf_info_t *info);

void set_info_owner(enum owner owner, shelf_info_t *info);

void set_info_name(char *name, shelf_info_t *info);

void set_info_id(char *id, shelf_info_t *info);

shelf_info_t *info_initiate(void);
