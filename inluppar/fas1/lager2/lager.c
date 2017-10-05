#include "common.h"
#include "list.h"
#include "tree.h"

typedef struct test
{
  char *a;
  int b;
} test_t;

void delete_func_aux(test_t *test)
{
  free(test->a);
}

void elem_delete_func(elem_t test)
{
  delete_func_aux(test.p);
  free(test.p);
}

int tree_compare_int(elem_t a, elem_t b)
{
  if (a.i == b.i) { return 0;}
  if (a.i > b.i) { return 1;}
  else { return -1;}
}

int main(int argc, char *argv[])
{
  tree_t *tree = tree_new(NULL, NULL, elem_delete_func, tree_compare_int);
  test_t *a = calloc(1, sizeof(test_t)); 
  elem_t elem = { .p = a };
  elem_t key = { .i = 1};
  tree_insert(tree, key, elem); 
  tree_delete(tree, true, true); 
  return 0;
}
