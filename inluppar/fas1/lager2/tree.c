#include "tree.h"
#include <assert.h>

#define Compare(a, b) (*tree)->cmp_f(a, b)
#define Current_key tree->key
#define Comp tree->cmp_f
#define Copy tree->copy_f
#define Free_elem tree->e_free_f
#define Free_key tree->k_free_f

struct tree
{
  tree_key_t key;
  elem_t elem;
  tree_t *right;
  tree_t *left;
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
  if (element_copy)
  {
    Copy = element_copy;
  }
  else
  {
    Copy = tree_no_copy;
  }
  if (key_free)     {Free_key = key_free;}
  if (elem_free)    {Free_elem = elem_free;}
  if (compare)      {Comp = compare;}
  return tree;
}

/// Remove a tree along with all elem_t elements.
///
/// \param tree the tree
/// \param delete_keys if true, run tree's key_free function on all keys
/// \param delete_elements if true, run tree's elem_free function on all elements
void tree_delete(tree_t *tree, bool delete_keys, bool delete_elements)
{
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

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree)
{
  if (!tree || (!(tree->left) && !(tree->right)))
  {
    return 0;
  }
  else
  {
    return 1 + max(tree_depth(tree->left), tree_depth(tree->right));  
  }
  
}

// Allmän traverseringsfunktion som används för insättning, sökning, djup och borttagning.
tree_t **tree_traverse(tree_t *tree, elem_t key)
{
  tree_t **c = &tree;
  while (*c)
  {
    if (tree->cmp_f(Current_key, key) == 0) { return c; }

    if (tree->cmp_f(Current_key, key) > 0) { c = &((*c)->right); }
    if (tree->cmp_f(Current_key, key) < 0) { c = &((*c)->left);  }
    
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
  // Trädet innehåller redan nyckeln
  if (tree_has_key(tree, key))
  {
    return false;
  }

  // Corner case för tomma träd
  if (tree->size == 0)
  {
    tree->elem = Copy(elem);
    tree->key = key;
    ++(tree->size);
  }
  
  else
  {
    tree_t **c = tree_traverse(tree, key); 
    tree_t *new = tree_new(tree->copy_f, tree->k_free_f, tree->e_free_f, tree->cmp_f);
    *c = new;
    (*c)->elem = Copy(elem);
    (*c)->key = key;
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
  tree_t **c = tree_traverse(tree, key);
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
  return false;
}
/// Removes the element for a given key in tree.
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_remove(tree_t *tree, tree_key_t key, elem_t *result)
{
  return false;
}

/// Returns an array holding all the keys in the tree
/// in ascending order.
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() keys
tree_key_t *tree_keys(tree_t *tree)
{
  return NULL;
}

/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements
elem_t *tree_elements(tree_t *tree)
{
  return NULL;
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
  return false;
}
