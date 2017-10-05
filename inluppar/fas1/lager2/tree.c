#include "tree.h"
#include <assert.h>

#define Compare(a, b) (*tree)->cmp_f(a, b)
#define Compare_keys tree->cmp_f((*c)->key, key)
#define Comp tree->cmp_f
#define Copy tree->copy_f
#define Free_elem tree->e_free_f
#define Free_key tree->k_free_f
#define Apply_key fun(node->key, node->elem, data)
#define Apply_left node_apply(node->left, order, fun, data)
#define Apply_right node_apply(node->right, order, fun, data)
#define Leaf !((*to_remove)->right || (*to_remove)->left)
#define Full (*to_remove)->right && (*to_remove)->left
#define Right (*to_remove)->right
#define Left (*to_remove)->left 
  
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
  
  for (int i = 0; i < (int)tree->size; ++i)
    {
      tree_remove(tree, keys[i], &result);
      Free_key(keys[i]);
    } 
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
  else
    {
      return 0;
    }


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
  else
    {
      return 0;
    }
}

// Allmän traverseringsfunktion som används för insättning, sökning, djup och borttagning.
/// Returnerar en dubbelpekare till ett träd som antingen är det som matchar 'key' eller ett
/// tomt subträd där vi borde ha hittat den.
node_t **tree_traverse(tree_t *tree, elem_t const key)
{
  node_t **c = &(tree->root);
  while (*c)
    {
      if (Compare_keys == 0) { return c; }

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
  if (tree_has_key(tree, key))
    {
      return false;
    }

  
  else
    {
      node_t **c = tree_traverse(tree, key); 
      node_t *new = node_new();
      new->elem = Copy(elem);
      new->key = key;
      *c = new;
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

// Frigör en nod i trädet
void free_node(tree_t *tree, node_t *node)
{
  Free_key(node->key);
  Free_elem(node->elem); 
  free(node);  
}

// Hittar den minsta efterträdaren till ett element i trädet
node_t **find_smallest_successor(node_t **node)
{
  while ((*node)->left)
    {
      node = &(*node)->left;
    }
  return node;
}


// Balanserar ett träd
node_t *tree_balance(elem_t elems[], elem_t keys[], int start, int end)
{
  // Base case
  if (start > end)
    return NULL;

  int middle = (start + end)/2;
  node_t *n  = node_new();
  n->elem    = elems[middle];
  n->key     = keys[middle]; 
 
  n->left =  tree_balance(elems, keys, start, middle-1); 
  n->right = tree_balance(elems, keys, middle+1, end);
 
  return n;
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
      *result = Copy((*to_remove)->elem); // Kopiera data 
      node_t *temp = *to_remove;

      // Två subträd
      if (Full)
        {
          node_t **replacement = find_smallest_successor(&(*to_remove)->right); 
          (*to_remove)->elem = Copy((*replacement)->elem);
          (*to_remove)->key  = Copy((*replacement)->key); 
          temp = *replacement;
          *replacement  = (*replacement)->right; 
        }
      
      // Höger subträd
      else if (Right) { (*to_remove) = (*to_remove)->right; }
      
      // Vänster subträd
      else if (Left) { (*to_remove) = (*to_remove)->right; }
      
      // Löv
      else if (Leaf) { *to_remove = NULL; }
      free_node(tree, temp); 
      --(tree->size);
      return true;
    }
  return false;
}

void tree_keys_aux(node_t *node, elem_t *keys, int *index)
{
  if (!node)
    {
      return;
    }
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
  int size = tree_size(tree);
  elem_t *keys = calloc(size, sizeof(elem_t));
  int index = 0;
  tree_keys_aux(tree->root, keys, &index);
  return keys;
}

void tree_elements_aux(node_t *node, elem_t *elems, int *index)
{
  if (!node)
    {
      return;
    }
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


bool node_apply(node_t *node, enum tree_order order, key_elem_apply_fun fun, void *data)
{
  if (node) {
   
    switch (order)
      {
      case inorder:  { return Apply_left || Apply_key   || Apply_right; }
      case preorder: { return Apply_key  || Apply_left  || Apply_right; }
      default:         return Apply_left || Apply_right || Apply_key;
      } 
  }
  
  return false; 
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
      return node_apply(tree->root, order, fun, data);
    }
  return false; 
}
