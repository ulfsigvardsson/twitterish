#include "tree.h"
#include <assert.h>

#define Compare(a, b) (*tree)->cmp_f(a, b)
#define Compare_keys tree->cmp_f((*c)->key, key)
#define Comp tree->cmp_f
#define Copy tree->copy_f
#define Free_elem tree->e_free_f
#define Free_key tree->k_free_f
#define Apply_key fun(node->key, node->elem, data)
#define Apply_left node_apply(node->left, order, fun, success, data)
#define Apply_right node_apply(node->right, order, fun, success, data)
#define Is_leaf !((*to_remove)->right || (*to_remove)->left)
#define Left  

struct node
{
  elem_t elem;
  tree_key_t key;
  node_t *left;
  node_t *right;
};

struct tree
{
  node_t *root;
  element_copy_fun copy_f;
  element_free_fun e_free_f;
  key_free_fun k_free_f;
  element_comp_fun cmp_f;
  size_t size;
};


elem_t tree_no_copy(elem_t elem)
{
  return elem;
}

void tree_no_free(elem_t elem)
{
  return;
}

node_t *node_new()
{
  node_t *node = calloc(1, sizeof(node_t));
  return node;
}


/// Creates a new tree
///
/// \param copy (may be NULL) a function applied to all elements when stored in the tree
/// \param key_free (may be NULL) used to free keys in tree_delete
/// \param elem_free (may be NULL) used to free elements in tree_delete
/// \param compare (may be NULL) used to compare keys
/// \returns: empty tree
tree_t *tree_new(element_copy_fun element_copy, key_free_fun key_free, element_free_fun elem_free, element_comp_fun compare)
{
  tree_t *tree = calloc(1, sizeof(tree_t));

  if (element_copy) {Copy = element_copy;}
  else {Copy = tree_no_copy;} 

  if (key_free)     {Free_key = key_free;}
  else { Free_key = tree_no_free; }

  if (elem_free)    {Free_elem = elem_free;}
  else { Free_elem = tree_no_free;}
  
  if (compare)      {Comp = compare;}
  tree->root = node_new();
  return tree;
 
}

/// Remove a tree along with all elem_t elements.
///
/// \param tree the tree
/// \param delete_keys if true, run tree's key_free function on all keys
/// \param delete_elements if true, run tree's elem_free function on all elements
void tree_delete(tree_t *tree, bool delete_keys, bool delete_elements)
{
  elem_t result;
  elem_t *keys = tree_keys(tree);
  int size = tree->size;
  
  for (int i = 0; i <= size; ++i)
    {
      tree_remove(tree, keys[i], &result); 
      if (delete_elements) Free_elem(result); 
    }
  //OM tree_size == 0 får vi göra något annat
  free(keys);
  free(tree->root); 
  free(tree);
  return;
}
/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree)
{
  return tree->size;
}

/// Returnerar det största av två heltal
int max(int a, int b)
{
  return a > b ? a : b;
}

int tree_depth_aux(node_t *node)
{
  if (node && (node->right || node->left))
    {
      return 1 + max(tree_depth_aux(node->left), tree_depth_aux(node->right));
    }

  return 0; 
}

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree)
{
  if (tree)
    {
      return tree_depth_aux(tree->root);
    } 

  return 0; 
}

// Allmän traverseringsfunktion som används för insättning, sökning, djup och borttagning.
/// Returnerar en dubbelpekare till ett träd som antingen är det som matchar 'key' eller ett
/// tomt subträd där vi borde ha hittat den.
node_t **tree_traverse(tree_t *tree, elem_t key)
{
  node_t **c = &(tree->root);
  
  while (*c)
    {
      if (Compare_keys == 0) return c;

      else if (Compare_keys < 0)
        {
          c = &((*c)->right);
        }
      else if (Compare_keys > 0)
        {
          c = &((*c)->left);
        }
    }
  return c;
}

/// Insert element into the tree. Returns false if the key is already used.
///
/// Uses the tree's compare function to compare keys.
///
/// If tree's copy function is non-NULL, it will be applied to
/// elem and its result stored in the tree. Otherwise, elem will
/// be stored in the tree. Note that keys are never copied and are
/// assumed to be immutable. (They may however be freed by the
/// tree.)
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended -- this is assumed to be an immutable value
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, tree_key_t key, elem_t elem)
{

  // Corner case för tomma träd
  if (tree->size == 0)
    {
      tree->root->elem = Copy(elem);
      tree->root->key = key;
      ++(tree->size);
    }

  // Trädet innehåller redan nyckeln
  else if (tree_has_key(tree, key))
    {
      return false;
    }

  
  else
    {
      node_t **c = tree_traverse(tree, key); 
      *c = node_new();
      (*c)->elem = Copy(elem);
      (*c)->key = key;
      /*
        node_t *new = node_new();
      new->elem = Copy(elem);
      new->key = key;
      *c = new;*/
      ++(tree->size);
    }
  return true;
}
/// Checks whether a key is used in a tree
///
/// Uses the tree's compare function to compare keys.
/// 
/// \param tree pointer to the tree
/// \param key the key to check for inclusion in the tree
/// \returns: true if key is a key in the tree
bool tree_has_key(tree_t *tree, tree_key_t key)
{
  node_t **c = tree_traverse(tree, key);
  return *c != NULL;
}

/// Finds the element for a given key in tree.
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_get(tree_t *tree, tree_key_t key, elem_t *result)
{
  node_t **c = tree_traverse(tree, key);

  if (*c)
    {
      *result = ((*c)->elem);
      return true;
    }
  else
    {
      return false;
    }
  
}

// Kanske måste sätta denn till dubbelpe
node_t **find_smallest_successor(node_t **node)
{
  while ((*node)->left)
    {
      *node = (*node)->left;
    }
  return node;
}

/// Removes the element for a given key in tree.
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_remove(tree_t *tree, tree_key_t key, elem_t *result)
{
  node_t **to_remove = tree_traverse(tree, key);
  
  if (*to_remove)
    {
      if ((*to_remove)->right && (*to_remove)->left)
        {
          node_t **minimum = find_smallest_successor(to_remove); // Elementet att ersätta med 
          (*to_remove)->elem = Copy((*minimum)->elem); // Kopiera data
          (*to_remove)->key = Copy((*minimum)->elem);
          *minimum = NULL; // Nolla pekaren till den minsta efterföljaren (?)
        }
      else if ((*to_remove)->right)
        {
          *result = Copy((*to_remove)->elem);
          --(tree->size);
          node_t *temp = *to_remove;
          *to_remove = (*to_remove)->right;
          free(temp);
        }
      else if ((*to_remove)->left)
        {
          
        } 
      else if (Is_leaf)
        { 
          *result = Copy((*to_remove)->elem);
          --(tree->size);
          free(*to_remove);
          (*to_remove) = NULL;
        }
     
      return true;
    }
  return false;
}

void tree_keys_aux(node_t *node, elem_t *keys, int *index)
{
  if (!node) return; 
  else
    {
      tree_keys_aux(node->left, keys, index);
      keys[*index] = node->key;
      ++(*index);
      tree_keys_aux(node->right, keys, index);
    }
}

/// Returns an array holding all the keys in the tree
/// in ascending order.
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() keys
tree_key_t *tree_keys(tree_t *tree)
{
  int size     = tree_size(tree);  
  elem_t *keys = calloc(size, sizeof(elem_t));
  int index    = 0;
  tree_keys_aux(tree->root, keys, &index);
  return keys;
}

void tree_elements_aux(node_t *node, elem_t *elems, int *index)
{
  if (!node) return; 
  else
    {
      tree_elements_aux(node->left, elems, index);
      elems[*index] = node->elem;
      ++(*index);
      tree_elements_aux(node->right, elems, index);
    }
}
/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements
elem_t *tree_elements(tree_t *tree)
{
  int size = tree_size(tree);
  elem_t *elems = calloc(size, sizeof(elem_t)); 
  int index = 0;
  tree_elements_aux(tree->root, elems, &index); 
  return elems;
}

bool node_apply(node_t *node, enum tree_order order, key_elem_apply_fun fun, bool *success, void *data)
{
  if (node) {
   
    switch (order)
      {
      case inorder:
        Apply_left;
        if (Apply_key)
          {
            *success = true;
          } 
        Apply_right;
        break;
      case preorder:
        if (Apply_key)
          {
            *success = true;
          }
        Apply_left;
        Apply_right;
        break;
      default: 
        Apply_left; 
        Apply_right; 
        if (Apply_key)
          {
            *success = true;
          }
        break; 
      } 
  }
  
  return *success; 
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
/// \returns the result of all fun calls, combined with OR (||)
bool tree_apply(tree_t *tree, enum tree_order order, key_elem_apply_fun fun, void *data)
{
  if (tree)
    {
      bool success = false;
      return node_apply(tree->root, order, fun, &success, data);
    }
  return false; 
}
