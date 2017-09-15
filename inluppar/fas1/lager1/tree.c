#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include "utils.h"
#include "db.h"
#include <stdio.h>

typedef struct node node_t;
struct node {
  K key;
  T item;
  list_t *l;  
};

struct tree {
  node_t *node;
  tree_t *left;
  tree_t *right;
};

//  tree_t t = { .left = nåt, .right = nåt, .key ="Vara", l = ['A23,', 'B5'] };
bool is_empty_tree(tree_t *tree);
void add_node(tree_t *tree, K key, T elem);

node_t *node_new() {
  node_t *new_node = calloc(1, sizeof(node_t));
  return new_node;
}

tree_t *tree_new() {
  tree_t *new_tree = calloc(1, sizeof(tree_t));
  return new_tree;
}


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
  return a > b ? a : b;
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
    ++depth;
    return ( biggest((tree_depth_help(tree->right, depth)), (tree_depth_help(tree->left, depth)))); 
  }
  
}

int tree_depth(tree_t *tree) {
  return tree_depth_help(tree, -1);
}


bool tree_has_key(tree_t *tree, K key) {
  if (tree->node == NULL) {
    return false;
  }
  else if (strcmp(tree->node->key, key) == 0) {
    return true;
  }
  else {
    return (tree_has_key(tree->left, key) || tree_has_key(tree->right, key));
  }
}

T tree_get(tree_t *tree, K key) {
  if (strcmp(tree->node->key, key) == 0) {
    return tree->node->item;
  }
  else if (!tree->left) {
    return tree_get(tree->right, key);
  }
  else if (!tree->right) {
    return tree_get(tree->left, key);
  }
  else {
    if (tree_has_key(tree->right, key)) {
      return(tree_get(tree->right, key));
    }
    else {
      return (tree_has_key(tree->right, key));
    }
  }
}



bool tree_insert( tree_t *tree, K key, T elem) {
  if (is_empty_tree(tree)) {
    node_t *new_node = node_new();
    new_node->key=key;
    new_node->item=elem;
    tree->node=new_node;
    return true;
  }
  if (tree_has_key(tree, key)) {
    return false;
  }
  
  else {
    if( strcmp(tree->node->key, key) < 0)  { // Vi kollar om vi ska till vänster
      if  (is_empty_tree(tree->left)) { // Kolla om vänsterträdet är tomt
        add_node(tree->left, key, elem); // Om ja, lägg till ett nytt träd till vänster
        return true;
      }
      else {
        return tree_insert(tree->left, key, elem); // Om inte, traversera vänsterträdet
      }
    }
    else { // Annars ska vi till höger
        if  (is_empty_tree(tree->right)) { // Kolla om högerrträdet är tomt
          add_node(tree->right, key, elem); // Om ja, lägg till ett nytt träd till höger
          return true;
        }
      else {
        return tree_insert(tree->right, key, elem); // Om inte, traversera högererträdet
      }
    }
  }
}

bool is_empty_tree(tree_t *tree) {
  return tree_size(tree) == 0;
}

void add_node(tree_t *tree, K key, T elem) {
  tree = tree_new(); // om ja: sätt vänsterträdet till ett tomt träd
  tree->node = node_new(); // och sätt dess nod till en tom nod
  tree->node->key = key;
  tree->node->item = elem;
}
