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
  elem_t elem1 = { .i = 1 };
  elem_t elem2 = { .i = 2 };
  elem_t result = { .i = 0 };
  list_insert(list, 0, elem1);
  list_insert(list, 1, elem2);
  CU_ASSERT_TRUE(list_length(list) == 2);
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, 2);
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
  elem_t elem2 = { .i = 2 };
  elem_t result = { .i = 0 };
  list_append(list, elem1);
  CU_ASSERT_TRUE(list_length(list) == 1);
  list_first(list, &result);
  CU_ASSERT_EQUAL(result.i , elem1.i);
  list_append(list, elem2);
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, 2);
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

void list_first_test()
{
  list_t *list  = list_new(NULL, NULL, NULL);
  elem_t elem1  = { .i = 1 };
  elem_t elem2  = { .i = 2 };
  elem_t result = { .i = 0 };
  list_first(list, &result); // Tom lista
  CU_ASSERT_EQUAL(result.i, 0);
  list_append(list, elem1);
  CU_ASSERT_TRUE(list_first(list, &result));
  CU_ASSERT_EQUAL( 1, result.i);
  list_prepend(list, elem2);
  CU_ASSERT_TRUE(list_first(list, &result));
  CU_ASSERT_EQUAL(2, result.i);
}

void list_last_test()
{
  list_t *list  = list_new(NULL, NULL, NULL);
  elem_t elem1  = { .i = 1 };
  elem_t elem2  = { .i = 2 };
  elem_t result = { .i = 0 };
  CU_ASSERT_FALSE(list_last(list, &result));
  CU_ASSERT_EQUAL(result.i, 0);
  list_append(list, elem1);
  CU_ASSERT_TRUE(list_last(list, &result));
  CU_ASSERT_EQUAL(1, result.i);
  list_prepend(list, elem2);
  CU_ASSERT_TRUE(list_last(list, &result));
  CU_ASSERT_EQUAL(1, result.i);
}

void list_remove_test()
{
  list_t *list  = list_new(NULL, NULL, NULL);
  elem_t elem1  = { .i = 1 };
  elem_t elem2  = { .i = 2 };
  elem_t result = { .i = 0 };

  list_remove(list, 0, false); // Kolla att programmet inte kraschar på tomma listor.
  
  list_append(list, elem2);
  list_append(list, elem1); // Denna är sist till en början

  CU_ASSERT_EQUAL(list_length(list), 2);
  list_remove(list, 1, false); // Nu ska elem2 vara sist och först
  CU_ASSERT_EQUAL(list_length(list), 1);
  list_last(list, &result);
  CU_ASSERT_EQUAL(result.i, elem2.i);
  list_first(list, &result);
  CU_ASSERT_EQUAL(result.i, elem2.i);
  list_append(list, elem1);
  CU_ASSERT_EQUAL(list_length(list), 2);
}

bool list_apply_fun(elem_t elem, void *data)
{
  if (elem.i < 2) {
     ++elem.i;
     return true;
  }
  return false;
}

void list_apply_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i = 1 };
  elem_t elem2 = { .i = 2 };
  elem_t elem3 = { .i = 3 };
  elem_t result = { .i = 0 };
  list_append(list, elem1);
  list_append(list, elem2);
  list_append(list, elem3);
  list_apply(list, list_apply_fun, NULL);
  for (int i = 0; i < 3; ++i) {
    list_get(list, i, &result);
    CU_ASSERT_TRUE(result.i >=2 );
  }
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
   CU_add_test(pSuite, "list_first", list_first_test);
   CU_add_test(pSuite, "list_last", list_last_test);
   CU_add_test(pSuite, "list_remove", list_remove_test);
   CU_add_test(pSuite, "list_apply", list_apply_test);
   

 
   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
  return 0;
}
