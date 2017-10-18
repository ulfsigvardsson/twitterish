#include <CUnit/Basic.h>
#include <stdio.h>
#include "list.h"
#include "common.h"
#include "tree.h"
#include "item.h"
#include "lager.h"
#include "undo.h"

int tree_compare_int(elem_t a, elem_t b)
{
  if (a.i == b.i) { return 0;}
  if (a.i > b.i) { return 1;}
  else { return -1;}
}


elem_t string_copy(elem_t elem)
{
  elem_t new = { .p= elem.p };
  return new;
}


int comp_fun_string(elem_t a, elem_t b)
{
  char *a_s = (char*)a.p;
  char *b_s = (char*)b.p;
  return strcmp(a_s, b_s);
}

void list_insert_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i = 1 };
  elem_t elem2 = { .i = 2 };
  elem_t elem3 = { .i = 3 };
  elem_t elem4 = { .i = 4 };
  elem_t result = { .i = 0 };
  
  list_insert(list, 0, elem1); 
  list_insert(list, 1, elem2);
  CU_ASSERT_TRUE(list_length(list) == 2);
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, 2);
  list_insert(list, 1, elem3);
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, elem3.i);
  list_get(list, 2, &result);
  CU_ASSERT_EQUAL(result.i, elem2.i);
  list_insert(list, -1, elem4);
  list_get(list, 3, &result); 
  CU_ASSERT_EQUAL(result.i, elem4.i);
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
  elem_t elem3 = { .i = 3 };
  elem_t result = { .i = 0 };
  list_append(list, elem1);
  CU_ASSERT_TRUE(list_length(list) == 1);
  list_first(list, &result);
  CU_ASSERT_EQUAL(result.i , elem1.i);
  list_append(list, elem2);
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, 2);
  list_append(list, elem3),
  list_get(list, 1, &result);
  CU_ASSERT_EQUAL(result.i, 2);
}

void list_prepend_test()
{
  list_t *list  = list_new(NULL, NULL, NULL);
  elem_t elem1  = { .i=1 };
  elem_t elem2  = { .i=2 };
  elem_t result = { .i = 0 };
  
  list_prepend(list, elem1);
  list_get(list, 0, &result);
  
  CU_ASSERT_TRUE(list_length(list) == 1);
  CU_ASSERT_EQUAL(result.i, 1);
  
  list_prepend(list, elem2);
  list_get(list, 0, &result);
  
  CU_ASSERT_EQUAL(result.i, elem2.i);
  CU_ASSERT_TRUE(list_length(list) == 2);
  
  list_get(list, 1, &result);
  
  CU_ASSERT_EQUAL(result.i, elem1.i);
}

void list_get_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i = 1 };
  elem_t elem2 = { .i = 2 };
  elem_t elem_get = { .i =0 };
  
  list_prepend(list, elem1);
  list_prepend(list, elem2);
  bool success = list_get(list, 1, &elem_get);

  CU_ASSERT_EQUAL(elem_get.i, elem1.i);
  CU_ASSERT_TRUE(success);

  list_get(list, -1, &elem_get);
  CU_ASSERT_EQUAL(elem_get.i, elem1.i);

  list_get(list, -2, &elem_get);
  CU_ASSERT_EQUAL(elem_get.i, elem2.i);
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
    return true;
  }
  return false;
}

void list_apply_test()
{
  list_t *list = list_new(NULL, NULL, NULL);
  elem_t elem1 = { .i = 1 };
  elem_t elem2 = { .i = 2 };
  elem_t elem3 = { .i = 0 };

  list_append(list, elem1);
  list_append(list, elem2);
  list_append(list, elem3);

  CU_ASSERT_TRUE(list_apply(list, list_apply_fun, NULL));
}

void list_contains_test()
{
  list_t *list = list_new(NULL, NULL, comp_fun_string);
  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem_not_in_list = { .p = "D"};
  list_append(list, elem1);
  list_append(list, elem2);
  list_append(list, elem3);
  int index = list_contains(list, elem2);
  CU_ASSERT_EQUAL(index, 1);
  index = list_contains(list, elem_not_in_list);
  CU_ASSERT_EQUAL(index, -1);
  index = list_contains(list, elem3);
  CU_ASSERT_EQUAL(index, 2);
}

void tree_new_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, NULL);
  CU_ASSERT_TRUE(tree != NULL);
}

void tree_insert_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);

  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "C" };
  
  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };

  
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key1, elem1);
  
  CU_ASSERT_TRUE(tree_has_key(tree, key1));
  CU_ASSERT_TRUE(tree_has_key(tree, key2));
}

void tree_height_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);

  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  
  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  
  tree_insert(tree, key1, elem1);
  int depth = tree_depth(tree);
  CU_ASSERT_EQUAL(depth, 0);
  tree_insert(tree, key2, elem2);
  depth = tree_depth(tree);
  CU_ASSERT_EQUAL(depth, 1);
  tree_insert(tree, key3, elem3);
  depth = tree_depth(tree);
  CU_ASSERT_EQUAL(depth, 2);
  tree_insert(tree, key4, elem4);

  depth = tree_depth(tree);
  CU_ASSERT_EQUAL(depth, 3);
}

void tree_get_test()
{
  tree_t *tree = tree_new(string_copy, NULL, NULL, tree_compare_int);

  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  elem_t result = { .p = "X "};

  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  elem_t key_not_in_tree = { .i = 5 };

  tree_insert(tree, key1, elem1);
  CU_ASSERT_TRUE(tree_get(tree, key1, &result));
  
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key3, elem3);
  tree_insert(tree, key4, elem4);
  CU_ASSERT_TRUE(tree_get(tree, key1, &result));
  CU_ASSERT_EQUAL(result.p, elem1.p);

  CU_ASSERT_FALSE(tree_get(tree, key_not_in_tree, &result));
  CU_ASSERT_EQUAL(result.p, elem1.p);
}

void tree_remove_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, comp_fun_string);

  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  
  elem_t key1 = { .p = "A" };
  elem_t key2 = { .p = "B" };
  elem_t key3 = { .p = "C" };
  elem_t key4 = { .p = "WHATEVS" };

  elem_t result = { .p = "RESULT" };

  tree_insert(tree, key2, elem2);
  tree_insert(tree, key1, elem1); 
  tree_insert(tree, key3, elem3);
  tree_insert(tree, key4, elem4);

  
  CU_ASSERT_TRUE(tree_size(tree) == 4); 
  tree_remove(tree, key1, &result); 

  CU_ASSERT_TRUE(strcmp("A", result.p) == 0);
  CU_ASSERT_TRUE(tree_size(tree) == 3); 
  CU_ASSERT_FALSE(tree_has_key(tree, key1)); 
  tree_remove(tree, key2, &result);
  
  CU_ASSERT_TRUE(strcmp("B", result.p) == 0);

  //  tree_remove(tree, key3, &result);
  //CU_ASSERT_TRUE(strcmp(elem3.p, result.p) == 0);
  //CU_ASSERT_TRUE(tree_size(tree) == 1);
  
}

void tree_elements_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);
  
  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  elem_t elem5 = { .p = "E" };
  elem_t elem6 = { .p = "F" };
  elem_t elem7 = { .p = "G" };

  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  elem_t key5 = { .i = 5 };
  elem_t key6 = { .i = 6 };
  elem_t key7 = { .i = 7 };

  tree_insert(tree, key7, elem7);
  tree_insert(tree, key4, elem4);
  tree_insert(tree, key1, elem1);
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key3, elem3);
  tree_insert(tree, key6, elem6);
  tree_insert(tree, key5, elem5);

  elem_t *keys = tree_keys(tree);

  for (int i = 0; i < 7; ++i)
    {
      CU_ASSERT_TRUE(keys[i].i == i+1);
    }
}

void tree_keys_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);
  
  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  elem_t elem5 = { .p = "E" };
  elem_t elem6 = { .p = "F" };
  elem_t elem7 = { .p = "G" };

  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  elem_t key5 = { .i = 5 };
  elem_t key6 = { .i = 6 };
  elem_t key7 = { .i = 7 };

  tree_insert(tree, key7, elem7);
  tree_insert(tree, key4, elem4);
  tree_insert(tree, key1, elem1);
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key3, elem3);
  tree_insert(tree, key6, elem6);
  tree_insert(tree, key5, elem5);

  elem_t *elems = tree_elements(tree);
  CU_ASSERT_TRUE(strcmp(elems[0].p, "A") == 0);
  CU_ASSERT_TRUE(strcmp(elems[6].p, "G") == 0);
}

void tree_delete_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);
  
  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  elem_t elem5 = { .p = "E" };
  elem_t elem6 = { .p = "F" };
  elem_t elem7 = { .p = "G" };

  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  elem_t key5 = { .i = 5 };
  elem_t key6 = { .i = 6 };
  elem_t key7 = { .i = 7 };

  tree_insert(tree, key7, elem7);
  tree_insert(tree, key4, elem4);
  tree_insert(tree, key1, elem1);
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key3, elem3);
  tree_insert(tree, key6, elem6);
  tree_insert(tree, key5, elem5);

  tree_delete(tree, false, true);
  CU_ASSERT_TRUE(tree_size(tree) == 0);
}

void tree_balance_test()
{
  tree_t *tree = tree_new(NULL, NULL, NULL, tree_compare_int);
  
  elem_t elem1 = { .p = "A" };
  elem_t elem2 = { .p = "B" };
  elem_t elem3 = { .p = "C" };
  elem_t elem4 = { .p = "D" };
  elem_t elem5 = { .p = "E" };
  elem_t elem6 = { .p = "F" };
  elem_t elem7 = { .p = "G" };

  elem_t key1 = { .i = 1 };
  elem_t key2 = { .i = 2 };
  elem_t key3 = { .i = 3 };
  elem_t key4 = { .i = 4 };
  elem_t key5 = { .i = 5 };
  elem_t key6 = { .i = 6 };
  elem_t key7 = { .i = 7 };

  tree_insert(tree, key1, elem1);
  tree_insert(tree, key2, elem2);
  tree_insert(tree, key3, elem3); tree_insert(tree, key4, elem4);

  CU_ASSERT_TRUE(strcmp("A", (char*)get_root_elem(tree)) == 0);

  tree_balance(&tree);
  
  CU_ASSERT_TRUE(strcmp("B", (char*)get_root_elem(tree)) == 0);
  
  tree_insert(tree, key5, elem5);
  tree_insert(tree, key6, elem6);
  tree_insert(tree, key7, elem7);

  tree_balance(&tree);
  
  CU_ASSERT_TRUE(strcmp("D", (char*)get_root_elem(tree)) == 0);
}


void item_new_test()
{
  item_t *item = item_new(strdup("Foo"), strdup("Bar"), 20);
  CU_ASSERT_TRUE(strcmp(item_name(item), "Foo") == 0);
  CU_ASSERT_TRUE(strcmp(item_descr(item), "Bar") == 0);
  CU_ASSERT_TRUE(item_price(item) == 20);
  
  item_set_name(item, "Lorem");
  item_set_description(item, "Ipsum");
  item_set_price(item, 100);

  CU_ASSERT_TRUE(strcmp(item_name(item), "Lorem") == 0);
  CU_ASSERT_TRUE(strcmp(item_descr(item), "Ipsum") == 0);
  CU_ASSERT_TRUE(item_price(item) == 100);

  list_t *shelves = item_shelves(item);
  CU_ASSERT_PTR_NOT_NULL(shelves);

  CU_ASSERT_TRUE(list_length(shelves) == 0);
}

void item_set_name_test()
{
  item_t *item = item_new(strdup("Foo"), strdup("Bar"), 20);
  item_set_name(item, "Lorem");
  CU_ASSERT_TRUE(strcmp(item_name(item), "Lorem") == 0);
}

void item_set_description_test()
{
  item_t *item = item_new(strdup("Foo"), strdup("Bar"), 20);
  item_set_description(item, "Ipsum");
  CU_ASSERT_TRUE(strcmp(item_descr(item), "Ipsum") == 0);
}

void item_set_price_test()
{
  item_t *item = item_new(strdup("Foo"), strdup("Bar"), 20);
  item_set_price(item, 100);
  CU_ASSERT_TRUE(item_price(item) == 100);
}

void shelf_new_test()
{
  shelf_t *shelf = shelf_new("A1", 10);
  CU_ASSERT_TRUE(strcmp(shelf_id(shelf), "A1") == 0);
  CU_ASSERT_TRUE(shelf_amount(shelf) == 10);
}

void item_set_shelf_test()
{
  shelf_t *shelf = shelf_new("A1", 10);
  item_set_shelf(shelf, "B1");
  CU_ASSERT_TRUE(strcmp(shelf_id(shelf), "B1") == 0);
}
/*
void item_set_amount_test()
{
  shelf_t *shelf = shelf_new("A1", 10);
  item_set_amount(shelf, 100);
  CU_ASSERT_TRUE(shelf_amount(shelf) == 100);
}
*/
void shelf_add_amount_test()
{
  shelf_t *shelf = shelf_new("A1", 10);
  shelf_add_amount(shelf, 100);
  CU_ASSERT_TRUE(shelf_amount(shelf) == 110);
}

void item_set_shelves_test()
{
  item_t *item = item_new("Foo", "Bar", 20);
  shelf_t *shelf = shelf_new("A1", 10);
  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);
  elem_t element = { .p = shelf };
  list_append(shelves, element); // Lägger till elementet i listan

  item_set_shelves(item, shelves); // Lägger till listan till item
  list_t* shelves2 = item_shelves(item);
  // Plockar fram listan igen och kollar längden
  CU_ASSERT_TRUE(list_length(shelves2) == 1);
  //Kollar elementet i listan
  elem_t shelf2 = { .p = NULL};
  CU_ASSERT_TRUE(list_get(shelves2, 0, &shelf2));
  shelf_t *shelf2_shelf = (shelf_t *)shelf2.p;
  
  CU_ASSERT_TRUE(strcmp(shelf_id(shelf2_shelf), "A1") == 0);
  CU_ASSERT_TRUE(shelf_amount(shelf2_shelf) == 10);
}

void shelf_compare_test()
{
  elem_t shelfA = { .p = shelf_new("A100", 1)};
  elem_t shelfB = { .p = shelf_new("B100", 1)};
  elem_t shelfC = { .p = shelf_new("A100", 1)};

  CU_ASSERT_TRUE(shelf_compare(shelfA, shelfB) != 0);
  CU_ASSERT_TRUE(shelf_compare(shelfA, shelfC) == 0);
}

void item_compare_test()
{
  elem_t key1 = { .p = "Kritor"};
  elem_t key2 = { .p = "Pennor"};
  elem_t key3 = { .p = "Kritor"};

  CU_ASSERT_TRUE(item_compare(key1, key2) != 0);
  CU_ASSERT_TRUE(item_compare(key1, key3) == 0);
}

void shelf_deep_copy_test()
{
  elem_t shelf1 = { .p = shelf_new("A1", 1)};
  elem_t shelf2 = shelf_deep_copy(shelf1);
  shelf_t *shelf2_shelf = shelf2.p;
  CU_ASSERT_TRUE(strcmp(shelf_id(shelf2_shelf), "A1") == 0);
  CU_ASSERT_TRUE(shelf_amount(shelf2_shelf) == 1);
}

void item_deep_copy_test()
{
  item_t *item1 = item_new("Foo", "Bar", 20);
  shelf_t *shelf = shelf_new("A1", 10);
  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);
  elem_t element1 = { .p = shelf };
  list_append(shelves, element1); // Lägger till elementet i listan
  item_set_shelves(item1, shelves); // Lägger till listan till item
  
  elem_t elem = { .p = item1};
  elem_t item2 = item_deep_copy(elem);

  CU_ASSERT_TRUE(strcmp(item_name(item1), item_name(item2.p)) == 0);
  CU_ASSERT_TRUE(strcmp(item_descr(item1), item_descr(item2.p)) == 0);
  CU_ASSERT_TRUE(item_price(item1) == item_price(item2.p));
  //Testar ifall hyllorna är lika
  list_t *item2_shelves = item_shelves(item2.p);
  elem_t element2 = { .p = NULL};
  CU_ASSERT_TRUE(list_get(item2_shelves, 0, &element2));
  CU_ASSERT_TRUE(shelf_compare(element1, element2) == 0);
  
}

void undo_new_test()
{
  undo_action_t *undo = undo_new();
  CU_ASSERT_TRUE(undo != NULL); 
}

void undo_reset_test()
{
  elem_t item = { .p = item_new("test", "ett test", 14) };
  undo_action_t *undo = undo_new();
  undo_set_last_action(undo, ADD);
  undo_set_added(undo, item);
  undo_reset(undo);
  CU_ASSERT_TRUE(undo_get_last_action(undo) == NOTHING);
  
  return;
}

void shelf_is_equal_test()
{
  elem_t shelf = { .p = shelf_new("A1", 2 )};
  shelf_info_t *info = shelf_info_new();
  set_info_id("A1", info);
  CU_ASSERT_TRUE(shelf_is_equal(shelf, info));
  return;
}

void shelf_is_in_list_test()
{
  shelf_info_t *info = shelf_info_new();
  set_info_name("Banan", info);
  set_info_id("A1", info);
  elem_t key    = { .p = "Banan" };
  elem_t item   = { .p = item_new("Banan", "En banan", 12) };
  
  elem_t shelf1 = { .p = shelf_new("A1", 1) };
  elem_t shelf2 = { .p = shelf_new("A2", 1) };

  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);
  list_append(shelves, shelf1);
  list_append(shelves, shelf2);
  item_set_shelves(item.p, shelves);

  CU_ASSERT_TRUE(shelf_is_in_list(key, item, info));
}

void merge_shelves_test()
{
  shelf_info_t *info = shelf_info_new();
  set_info_id(strdup("A3"), info);
  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);
  elem_t shelf1   = { .p = shelf_new(strdup("A1"), 1) };
  elem_t shelf2   = { .p = shelf_new("A2", 1) };
  
  list_append(shelves, shelf1);
  list_append(shelves, shelf2);

  merge_shelves(info, shelf1, shelves);
  elem_t temp = { .p = shelf_new("A1", 1) };
  CU_ASSERT_FALSE(list_contains(shelves, temp));
}

int main(int argc, char *argv[]) {
  CU_pSuite listSuite  = NULL;
  CU_pSuite treeSuite  = NULL;
  CU_pSuite itemSuite  = NULL;
  CU_pSuite lagerSuite = NULL;
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  listSuite = CU_add_suite("List.h", NULL, NULL);

  /* add the tests to the suite */
  CU_add_test(listSuite, "new_list", list_new_test);
  CU_add_test(listSuite, "list_insert", list_insert_test);
  CU_add_test(listSuite, "list_prepend", list_prepend_test);
  CU_add_test(listSuite, "list_append", list_append_test);
  CU_add_test(listSuite, "list_get", list_get_test);
  CU_add_test(listSuite, "list_first", list_first_test);
  CU_add_test(listSuite, "list_last", list_last_test);
  CU_add_test(listSuite, "list_remove", list_remove_test);
  CU_add_test(listSuite, "list_apply", list_apply_test);
  CU_add_test(listSuite, "list_contains", list_contains_test);
   
  
  treeSuite = CU_add_suite("Tree.h", NULL, NULL);
  CU_add_test(treeSuite, "tree_new", tree_new_test);
  CU_add_test(treeSuite, "tree_insert", tree_insert_test);
  CU_add_test(treeSuite, "tree_height", tree_height_test);
  CU_add_test(treeSuite, "tree_get", tree_get_test);
  CU_add_test(treeSuite, "tree_remove", tree_remove_test);
  CU_add_test(treeSuite, "tree_elements", tree_elements_test);
  CU_add_test(treeSuite, "tree_keys", tree_keys_test);
  CU_add_test(treeSuite, "tree_balance", tree_balance_test);
  CU_add_test(treeSuite, "tree_delete", tree_delete_test);

  itemSuite = CU_add_suite("Item.h", NULL, NULL);
  CU_add_test(itemSuite, "item_new", item_new_test);
  CU_add_test(itemSuite, "item_set_name", item_set_name_test);
  CU_add_test(itemSuite, "item_set_description", item_set_description_test);
  CU_add_test(itemSuite, "item_set_price", item_set_price_test);
  CU_add_test(itemSuite, "shelf_new", shelf_new_test);
  CU_add_test(itemSuite, "item_set_shelf", item_set_shelf_test);
  //CU_add_test(itemSuite, "item_set_amount", item_set_amount_test);
  //Cunit hittar inte item_set_amount FIXME
  CU_add_test(itemSuite, "shelf_add_amount", shelf_add_amount_test);
  CU_add_test(itemSuite, "item_set_shelf", item_set_shelf_test);
  CU_add_test(itemSuite, "item_set_shelves", item_set_shelves_test);
  CU_add_test(itemSuite, "shelf_compare", shelf_compare_test);
  CU_add_test(itemSuite, "item_compare", item_compare_test);
  CU_add_test(itemSuite, "shelf_deep_copy", shelf_deep_copy_test);
  CU_add_test(itemSuite, "item_deep_copy", item_deep_copy_test);

  lagerSuite = CU_add_suite("Lager.h", NULL, NULL);
  CU_add_test(lagerSuite, "shelf_is_equal", shelf_is_equal_test);
  CU_add_test(lagerSuite, "undo_reset", undo_reset_test);
  CU_add_test(lagerSuite, "shelf_is_in_list", shelf_is_in_list_test);
  CU_add_test(lagerSuite, "merge_shelves", merge_shelves_test);
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
  return 0;
}
