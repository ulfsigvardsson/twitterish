#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "item.h"
#include "saveinfo.h"


void test_list_new(void) {
  list_t *lista = list_new();
  CU_ASSERT_TRUE(lista != NULL);
 
}

void test_list_append(void) {
  list_t *lista = list_new();
  int tal = 1;
  int tal2 = 2;
  list_append(lista, &tal);
  CU_ASSERT_TRUE(**(int**)list_last(lista) == 1);
  list_append(lista, &tal2);
  CU_ASSERT_TRUE(**(int**)list_last(lista) == 2);
  
  free(lista);
}

void test_list_prepend(void) {
  list_t *lista = list_new();
  int tal = 1;
  int tal2 = 2;
  list_prepend(lista, &tal);
  CU_ASSERT_TRUE(**(int**)list_first(lista) == 1);
  list_prepend(lista, &tal2);
  CU_ASSERT_TRUE(**(int**)list_first(lista) == 2);
  
  free(lista);
}

void test_list_length(void) {
  list_t *lista = list_new();
  int tal = 1;
  int tal2 = 2;
  CU_ASSERT_TRUE(list_length(lista) == 0);
  list_append(lista, &tal);
  CU_ASSERT_TRUE(list_length(lista) == 1);
  list_append(lista, &tal2);
  CU_ASSERT_TRUE(list_length(lista) == 2);
  
  free(lista);
}

void test_list_insert(void) {
  list_t *lista = list_new();
  int tal = 1;
  int tal2 = 2;
  int tal3 = 3;
  list_insert(lista, 0, &tal);
  CU_ASSERT_TRUE(list_length(lista) == 1);
  CU_ASSERT_TRUE(**(int**)list_first(lista) == 1);
  list_append(lista, &tal2);
  list_insert(lista, -1, &tal3);
  list_insert(lista, 1, &tal3);
  list_insert(lista, 10, &tal3);
  CU_ASSERT_TRUE(list_length(lista) == 4);
  
  free(lista);
}

void test_list_remove(void) {
  list_t *lista = list_new();
  int tal =1;
  void *tal2;
  CU_ASSERT_FALSE(list_remove(lista, 2, &tal2));
  list_append(lista, &tal);
  CU_ASSERT_TRUE(list_remove(lista, 0, &tal2));
  CU_ASSERT_TRUE(*(int*)tal2 == 1);
  CU_ASSERT_FALSE(list_remove(lista, 1, &tal2));
  
  free(lista);
}

void test_list_get(void) {
  list_t *lista = list_new();
  int tal = 1;
  int tal2 = 2;
  int tal3 = 3;
  list_append(lista, &tal);
  CU_ASSERT_TRUE(**(int**)list_get(lista, 0) == 1);
  list_append(lista, &tal2);
  list_append(lista, &tal3);
  CU_ASSERT_TRUE(**(int**)list_get(lista, 2) == 3);
  list_prepend(lista, &tal3);
  CU_ASSERT_TRUE(**(int**)list_get(lista, 0) == 3);
  free(lista);
}

void test_list_apply(void) {
    list_t *lista = list_new();
    /* int tal = 1;
  int tal2 = 2;
  int tal3 = 3;

  FIXA!   */
  
  free(lista);
}


// ----------------------------------------------------------------//
//                 TEST TREE -- TEST TREE                          //
// ----------------------------------------------------------------//




void test_tree_new(void) {
  tree_t *tree = tree_new();
  CU_ASSERT_TRUE(tree != NULL);
  
  free(tree);
}

void test_tree_insert(void) {
  tree_t *tree = tree_new();
  CU_ASSERT_TRUE(tree_insert(tree, "banan", "god"));
  CU_ASSERT_TRUE(tree_insert(tree, "groda", "grön"));
  CU_ASSERT_TRUE(tree_size(tree) == 2);
  CU_ASSERT_TRUE(tree_depth(tree) == 1);
  tree_insert(tree, "apa", "brun");
  CU_ASSERT_TRUE(tree_size(tree) == 3);
  CU_ASSERT_TRUE(tree_depth(tree) == 1);
  tree_insert(tree,"apa", "brun");
  CU_ASSERT_TRUE(tree_size(tree) == 3);
  CU_ASSERT_TRUE(tree_depth(tree) == 1);

  // tree_delete(tree);
}

void test_tree_size(void) {
  tree_t *tree = tree_new();
  
  
  free(tree);
}


void test_tree_depth(void) {
  tree_t *tree = tree_new();
  
  free(tree);
}



void test_tree_has_key(void) {
  tree_t *tree = tree_new();

  
  free(tree);
}


void test_tree_get(void) {
  tree_t *tree = tree_new();
  
  free(tree);
}



void test_tree_keys(void) {
  tree_t *tree = tree_new();

  
  free(tree);
}

void test_tree_elements(void) {
  tree_t *tree = tree_new();

  
  free(tree);
}


int main(int argc, char *argv[]) {

  // Sätter upp testet.
  CU_initialize_registry();


  CU_pSuite list = CU_add_suite("Test list functions", NULL, NULL);
  CU_add_test(list, "New list", test_list_new);
  CU_add_test(list, "List append", test_list_append);
  CU_add_test(list, "List prepend", test_list_prepend);
  CU_add_test(list, "List length", test_list_length);
  CU_add_test(list, "List insert", test_list_insert);
  CU_add_test(list, "List remove", test_list_remove);
  CU_add_test(list, "List get", test_list_get);
  CU_add_test(list, "List apply", test_list_apply);
  

  CU_pSuite tree = CU_add_suite("Test tree functions", NULL, NULL);
  CU_add_test(tree, "Tree new", test_tree_new);
  CU_add_test(tree, "Tree insert", test_tree_insert);
  CU_add_test(tree, "Tree size", test_tree_size);  
  CU_add_test(tree, "Tree depth", test_tree_depth);
  CU_add_test(tree, "Tree has_key", test_tree_has_key);
  CU_add_test(tree, "Tree get", test_tree_get);
  CU_add_test(tree, "Tree keys", test_tree_keys);
  CU_add_test(tree, "Tree elements", test_tree_elements);
//CU_add_test(tree, "Tree apply", test_tree_apply);    hur??
//CU_add_test(tree, "Tree remove", test_tree_remove);


  //run the tests.
  CU_basic_run_tests();

  //shutdown.
  CU_cleanup_registry();

  
  return 0;
}
