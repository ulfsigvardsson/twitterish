#include <stdlib.h>
#include <stdbool.h>

enum owner {OTHER, NONE, SELF};


typedef struct save_info save_info_t;

save_info_t *save_info_new();

bool info_exists(save_info_t *info);

enum owner info_owner(save_info_t *info);

char *info_name(save_info_t *info);

char *info_id(save_info_t *info);

void set_info_exists(bool val, save_info_t *info);

void set_info_owner(enum owner owner, save_info_t *info);

void set_info_name(char *name, save_info_t *info);

void set_info_id(char *id, save_info_t *info);

save_info_t *info_initiate(void);
