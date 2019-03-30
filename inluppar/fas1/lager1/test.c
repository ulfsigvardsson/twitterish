#include <CUnit/Basic.h>
#include "list.h"


void test_list_new() {
  list_t *list = list_new();
  CU_ASSERT_TRUE(list != NULL);
}

int main(int argc, char *argv[]) {
  CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Lista", NULL, NULL);

   /* add the tests to the suite */
   CU_add_test(pSuite, "list_new", test_list_new);

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
  return 0;
}
