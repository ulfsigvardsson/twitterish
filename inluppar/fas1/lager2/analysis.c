#include "tree.h"
#include "list.h"
#include "common.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  tree_t *tree = tree_new(NULL, NULL, NULL, NULL);

  for (int i = 0; i < 10000; i++) {
    elem_t elem = { .i = i};
    tree_insert(tree, elem, elem);
    printf("%d\n", i );
    tree_balance(&tree);
  }
  
  return 0;
}
