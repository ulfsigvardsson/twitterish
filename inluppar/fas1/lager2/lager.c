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

void delete_func(elem_t test)
{
  delete_func_aux(test.p);
  free(test.p);
}

int main(int argc, char *argv[])
{
  list_t *list = list_new(NULL, delete_func, NULL);
  test_t *a = calloc(1, sizeof(test_t));
  elem_t elem = { .p = a };
  list_append(list, elem);
  list_delete(list, true);
  return 0;
}
