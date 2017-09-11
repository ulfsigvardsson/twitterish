#include "tree.h"
#include "db.h"

typedef struct tree_node node_t;

struct tree_node {
  node_t left;
  node_t right;
  char *key;
};
