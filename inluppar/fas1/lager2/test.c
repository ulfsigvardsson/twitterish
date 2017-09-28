#include <CUnit/Basic.h>
#include "list.h"
#include "common.h"

void list_remove_fun_string_aux(char *elem)
{
  free(elem);
}

void free_string(elem_t elem) {
  list_remove_fun_string_aux(elem.p);
}

size_t comp_fun_string(elem_t a, elem_t b)
{
  return strcmp(a.p, b.p);
}

void list_insert_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem = { .i = 1 };
  list_insert(list, 0, elem);
  CU_ASSERT_TRUE(list_length(list) == 1);
  
}
                    

void list_new_test()
{
  list_t *new = list_new(NULL, NULL, NULL);
  CU_ASSERT_FALSE(new == NULL);
}

void list_append_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i = 1 };
  list_append(list, elem1);
  CU_ASSERT_TRUE(list_length(list) == 1);
}

void list_prepend_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i=1};
  elem_t elem2 = { .i=2};
  list_prepend(list, elem1);
  CU_ASSERT_TRUE(list_length(list) == 1);
  list_prepend(list, elem2);
  CU_ASSERT_TRUE(list_length(list) == 2);
}

void list_get_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i=1};
  elem_t elem2 = { .i=2};
  elem_t *elem_get = calloc(1, sizeof(elem_t));
  list_prepend(list, elem1);
  list_prepend(list, elem2);
  bool success = list_get(list, 1, elem_get);
  CU_ASSERT_TRUE(elem_get->i == elem1.i);
  CU_ASSERT_TRUE(success);                           
}

int main(int argc, char *argv[]) {
  CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("List.h", NULL, NULL);

   /* add the tests to the suite */
   CU_add_test(pSuite, "new_list", list_new_test);
   CU_add_test(pSuite, "list_insert", list_insert_test);
   CU_add_test(pSuite, "list_prepend", list_prepend_test);
   CU_add_test(pSuite, "list_append", list_append_test);
   CU_add_test(pSuite, "list_get", list_get_test);   
   //CU_add_test(pSuite, "list_insert", list_insert_test);
 
   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
  return 0;
}
