#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include "utils.h"
#include "db.h"
#include <stdio.h>

struct node {
  K key;    
  list_t *l;  
};

struct tree {
  node_t *node;
  tree_t *left;
  tree_t *right;
};

//  tree_t t = { .left = nåt, .right = nåt, .key ="Vara", l = ['A23,', 'B5'] };

node_t *node_new() {
  node_t *new_node = calloc(1, sizeof(node_t));
  return new_node;
}

tree_t *tree_new() {
  tree_t *new_tree = calloc(1, sizeof(tree_t));
  return new_tree;
}

// void tree_delete(tree_t *tree) {
//  }

int tree_size(tree_t *tree) {
  if (tree->node == NULL) {
    return 0;
  }
  else if (!tree->right && !tree->left) {    // om det är ett löv
    return 1;
  }
  else if (!tree->right) {                   // om vänstra sidan förgrenar sig
    return ( 1 + tree_size(tree->left));
  }
  else if (!tree->left) {                    // om högra sidan förgrenar sig
    return ( 1 + tree_size(tree->right));  
  }
  else {                                      // om båda sidorna förgrenar sig
    return ( 1 + tree_size(tree->left) + tree_size(tree->right));
  }
}

int biggest(int a, int b) {
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}

int tree_depth_help(tree_t *tree, int depth) {
  if (tree->node == NULL) {
    return depth;
  }
  else if (!tree->right && !tree->left) {
    return depth+1;
  }
  else if (!tree->right) {
    return ( tree_depth_help(tree->left, depth+1));
  }
  else if (!tree->left) {
    return ( tree_depth_help(tree->right, depth+1));
  }
  else {
    return ( biggest((tree_depth_help(tree->right, depth+1)), (tree_depth_help(tree->left, depth+1)))); 
  }
  
}

int tree_depth(tree_t *tree) {
  return tree_depth_help(tree, -1);
}

bool tree_insert( tree_t *tree, K key, T elem) {
  

  
}




