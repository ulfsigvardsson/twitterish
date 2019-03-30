#include <stdbool.h>
#include <stdlib.h>

enum owner {OTHER, NONE, SELF};

typedef struct shelf_info shelf_info_t;


shelf_info_t *shelf_info_new();
char *info_name(shelf_info_t *info);
bool info_exists(shelf_info_t *info);
char* info_shelf(shelf_info_t *info);
enum owner info_owner(shelf_info_t *info);
void set_info_exist(bool val, shelf_info_t *info);
void set_info_owner(shelf_info_t *info, enum owner owner);
void set_info_name(shelf_info_t *info, char *name);
void set_info_shelf(shelf_info_t *info, char *shelf);
