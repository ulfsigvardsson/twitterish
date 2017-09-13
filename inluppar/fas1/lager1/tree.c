#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include <stdio.h>


struct tree {
  tree_t *left;
  tree_t *right;
  K key;
  list_t *l;
};

//  tree_t t = { .left = nåt, .right = nåt, .key ="Vara", l = ['A23,', 'B5'] };

tree_t *tree_new() {
  tree_t *new_tree = calloc(1, sizeof(tree_t));
  return new_tree;
}

void tree_delete(tree_t *tree) {
  

}
