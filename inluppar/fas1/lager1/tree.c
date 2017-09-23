#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include "utils.h"
#include "item.h"
#include <stdio.h>

typedef struct node node_t;
struct node {
  K key;
  T *item;
};

enum branch {EMPTY, EMPTY_LEAF, LEAF, LEFT, RIGHT, FULL};

struct tree {
  node_t *node;
  tree_t *left;
  tree_t *right;
};

//  tree_t t = { .left = nåt, .right = nåt, .key ="Vara", l = ['A23,', 'B5'] };

void add_subtree(tree_t **tree, K key, T elem);
void initiate_tree(tree_t *tree, K key, T elem);
void tree_insert_aux(tree_t *tree, K key, T elem, int direction);
void tree_keys_aux(tree_t *tree, K *keys, int *index);

// Returnerar vilka branches som finns på trädet, om några alls
enum branch tree_branches(tree_t *tree) {
  enum branch type; 
  if (!tree) {
    type = EMPTY;
  }
  else if (!tree->right && !tree->left && !tree->node) {
    type = EMPTY_LEAF;
  }
  else if (!tree->right && !tree->left) {
    type = LEAF;
  }
  else if (tree->right && tree->left){
    type = FULL;
  }
  else if (tree->right) {
    type = RIGHT;
  }
  else {
    type = LEFT;
  }

  return type;
}

node_t *node_new() {
  node_t *new_node = calloc(1, sizeof(node_t));
  return new_node;
}

tree_t *tree_new() {
  tree_t *new_tree = calloc(1, sizeof(tree_t));
  return new_tree;
}


int tree_size(tree_t *tree) {
  enum branch type = tree_branches(tree);

  switch (type) {
    case EMPTY: {
      return 0;
    }
    case EMPTY_LEAF: {
      return 0;
    }
    case LEAF: {
      return 1;
    }    
    case LEFT: {
      return 1 + tree_size(tree->left);
    }
    case RIGHT: {
      return 1 + tree_size(tree->right);
    }
    default: {
      return 1 + tree_size(tree->left) + tree_size(tree->right);
    }
  }
}

int biggest(int a, int b) {
  return a > b ? a : b;
}

int tree_depth_aux(tree_t *tree, int depth) {
  enum branch type = tree_branches(tree);

  switch (type) {
    case EMPTY: {
      return depth;
      break;
    }
    case LEAF: {
      return depth+1;
      break;
    }
    case LEFT: {
      return ( tree_depth_aux(tree->left, depth+1));
      break;
    }
    case RIGHT: {
      return ( tree_depth_aux(tree->right, depth+1));
      break;
    }
    case FULL: {
      ++depth;
      return ( biggest((tree_depth_aux(tree->right, depth)), (tree_depth_aux(tree->left, depth))));
      break;
    }
    default: {
      return -1; 
    }
  }
}


int tree_depth(tree_t *tree) {
  return tree_depth_aux(tree, -1);
}

bool matching_keys(node_t *node, K key) {
  return strcmp(node->key, key) == 0;
}

bool tree_has_key(tree_t *tree, K key) {
  enum branch type = tree_branches(tree);
  if (!tree || !tree->node) { // Om noden eller trädet är NULL
    return false;
  }
  else {
    switch (type) {
      case EMPTY: { return false;}
      case LEAF:  { return matching_keys(tree->node, key);}
      case LEFT:  { return (matching_keys(tree->node, key) ||
                            tree_has_key(tree->left, key));
      }
      case RIGHT: { return (matching_keys(tree->node, key) ||
                            tree_has_key(tree->right, key));
      }
      case FULL:  { return (matching_keys(tree->node, key) ||
                            tree_has_key(tree->left, key) ||
                            tree_has_key(tree->right, key));
      }
      default :   { return false;}
    }
  }
}


T tree_get(tree_t *tree, K key) {
  enum branch type = tree_branches(tree);

  // Ingen EMPTY eftersom vi antar att nyckeln existerar
  switch (type) {
    case LEAF:  { return tree->node->item;                 }
    case LEFT: {
      if (matching_keys(tree->node, key)) {
        return tree->node->item;
      }
      else {
        return tree_get(tree->left, key);
      }
    }
    case RIGHT: {
      if (matching_keys(tree->node, key)) {
        return tree->node->item;
      }
      else {
        return tree_get(tree->right, key);
      }
    }
    default:  {
      if (matching_keys(tree->node, key)) {
        return tree->node->item;
      }
      else if (tree_has_key(tree->right, key)){
        return tree_get(tree->right, key);
      }
      else {
        return tree_get(tree->left, key);
      }
    }
  }
}

bool tree_insert( tree_t *tree, K key, T elem) {
  enum branch type = tree_branches(tree);
  
  if (!type) { // Om trädet är tomt, dvs. EMPTY = 0, initierar vi ett nytt träd
    initiate_tree(tree, key, elem);
    return true;
  }
  
  else if (tree_has_key(tree, key)) { // Om trädet finns men nyckeln redan finns avslutas funktionen
    return false;
  }
  else { // Annars kollar vi cases
    switch (type) {
      case EMPTY_LEAF: { // Om trädet finns men noden är NULL skapar vi en ny nod
        tree->node = node_new();
        tree->node->key = key;
        tree->node->item = elem;
        return true;
      }
      default :   {
        int direction = strcmp(key, tree->node->key);
        tree_insert_aux(tree, key, elem, direction);
      }
    }
  }
  return true;
}


// Hjälpfunktion för tree_insert. Gör korrekt förgreningsval beroende på key och typ av subträd

void tree_insert_aux(tree_t *tree, K key, T elem, int direction) {
  if (direction < 0 && !tree->left) { 
    add_subtree(&(tree->left), key ,elem); // add_subtree &tree->left. 
  }
  else if (direction < 0) {
    tree_insert(tree->left, key ,elem);    // tree_insert tree->left
  }
  else if (!tree->right){
    add_subtree(&tree->right, key, elem); // add_subtree &tree->right
  }
  else {
    tree_insert(tree->right, key, elem);
  }
}


/// Lägger till ett nytt subträd till ett träd
///
/// \param tree-pekare till en pekare till ett träd
/// \param key nyckel till den nya noden
/// \param elem element till den nya noden
/// \returns: void
//FIXME: vi skickar in trädet, inte dess subträd här. trädet ersätts av ett nytt.
void add_subtree(tree_t **tree, K key, T elem) {
  (*tree) = tree_new(); // Trädet som skickas in är NULL, vi pekar därför om pekaren till ett nytt träd
  (*tree)->node = node_new(); 
  (*tree)->node->key = key;
  (*tree)->node->item = elem;
}

/// Initiera ett tomt, dock !NULL, träd med en nod.
///
/// \param tree-pekare till ett träd
/// \param key nyckel till den nya noden
/// \param elem element till den nya noden
/// \void
void initiate_tree(tree_t *tree, K key, T elem) {
    node_t *new_node = node_new();
    new_node->key=key;
    new_node->item=elem;
    tree->node=new_node;
}
//////////// ================= Added in version 1.2
///
/// NOTE: Implementing these functions is NOT mandatory
///

/// Returns an array holding all the keys in the tree
/// in ascending order.///
/// \param tree pointer to the tree
/// \returns: array of tree_size() keys
K *tree_keys(tree_t *tree)  {
  int size = tree_size(tree);
  K *keys = calloc(size, sizeof(K));
  int *index = calloc(1, sizeof(int));
  *index = 0;
  tree_keys_aux(tree, keys, index);
  free(index);
  return keys;
}

void tree_keys_aux(tree_t *tree, K *keys, int *index) {
  if (!tree) {
    return;
  }
  else {
    tree_keys_aux(tree->left, keys, index);
    keys[*index] = tree->node->key;
    ++(*index);
    tree_keys_aux(tree->right, keys, index);
  }
}

void tree_elements_aux(tree_t *tree, T *elems, int *index) {
  if (!tree) {
    return;
  }
  else {
    tree_elements_aux(tree->left, elems, index);
    elems[*index] = tree->node->item;
    ++(*index);
    tree_elements_aux(tree->right, elems, index);
  }
}


/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements




T *tree_elements(tree_t *tree) {
  int size = tree_size(tree);
  T *elems = calloc(size, sizeof(T));
  int *index = calloc(1, sizeof(int));
  *index = 0;
  tree_elements_aux(tree, elems, index);
  free(index);
  return elems;
}

/// Applies a function to all elements in the tree in a specified order.
/// Example (using shelf as key):
///
///     tree_t *t = tree_new();
///     tree_insert(t, "A25", some_item);
///     int number = 0;
///     tree_apply(t, inorder, print_item, &number);
///
/// where print_item is a function that prints the number and increments it,
/// and prints the item passed to it. 
///
/// \param tree the tree
/// \param order the order in which the elements will be visited
/// \param fun the function to apply to all elements
/// \param data an extra argument passed to each call to fun (may be NULL)

void tree_apply(tree_t *tree, enum tree_order order, tree_action2 fun, void *data) {
if (!tree) {
    return;
  }
  else {
    enum branch branch = tree_branches(tree);

    if (branch == LEAF) {
      fun(tree->node->key, tree->node->item, data);
    }
    else { 
      switch (order) {
        case inorder: {
          tree_apply(tree->left, order, fun, data);
          fun(tree->node->key, tree->node->item, data);
          tree_apply(tree->right, order, fun, data);
          break;
        }
        case preorder: {
          fun(tree->node->key, tree->node->item, data);
          tree_apply(tree->left, order, fun, data);
          tree_apply(tree->right, order, fun, data);
          break;
        }
        default:
          tree_apply(tree->left, order, fun, data);
          tree_apply(tree->right, order, fun, data);
          fun(tree->node->key, tree->node->item, data);
          break;
        }
    }
  }  
}
