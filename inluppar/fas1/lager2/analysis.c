#include "item.h"
#include "tree.h"
#include "list.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  tree_t *tree = tree_new(NULL, NULL, NULL, NULL);

  for (int i = 0; i < 100000; ++i) {
    elem_t c = { .i = i };
tree_insert(tree, c, c);
printf("%d\n", i);
}

  for (int i = 0; i < 100000; ++i) {
    elem_t result;
elem_t key = { .i = i };
tree_get(tree, key, &result);
 printf("%d\n", i);
 }
return 0;
}
