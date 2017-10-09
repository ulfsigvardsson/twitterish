#include "file.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "r");
  char name[20], descr[100];
  int price, shelf_count;
  
  
  while (1)
    { //Om inläsningen av nästa namn är tomt har vi nått slutet av filen
      if (!fgets(name, 20, f))
        {
          break;
        }
      
      fgets(descr, 100, f); // Beskrivningen är troligtvis flera ord, därav fgets() 
      fscanf(f, "%d ", &price);
      fscanf(f, "%d ", &shelf_count);

      printf("Namn: %s", name);
      printf("Beskrivning: %s", descr);
      printf("Pris: %d\n", price);
      printf("Hylla\tAntal\n");
      
      char id[3 ];
      int amount;
      
      for (int i = 0; i < shelf_count; ++i)
        {
          fscanf(f, "%s%d ", id, &amount);
          printf("%s\t%d\n", id, amount);
        }
  
    }
 
  fclose(f);
  return 0;
}

tree_t *load_db(char *filepath)
{
  tree_t *db = tree_new(item_copy, string_free, item_free, item_compare);
  
  //Lägg in case för om filen inte finns!
  FILE *f = fopen(filepath, "r");
  char name[20], descr[100];
  int price, shelf_count;
  list_t *shelves = list_new(shelf_copy, shelf_free, shelf_compare);
  
  while (1)
    { //Om inläsningen av nästa namn är tomt har vi nått slutet av filen
      if (!fgets(name, 20, f))
        {
          break;
        }
      
      fgets(descr, 100, f); // Beskrivningen är troligtvis flera ord, därav fgets() 
      fscanf(f, "%d ", &price);
      fscanf(f, "%d ", &shelf_count);
      
      item_t *item = item_new(name, descr, price, shelves);
        
      char id[3];
      int amount;

      //Misstänker att saker behöver kopieras med item_copy etc. för att inte skrivas över.
      for (int i = 0; i < shelf_count; ++i)
        {
          fscanf(f, "%s%d ", id, &amount);
          shelf_t *shelf = shelf_new(id, amount);
          elem_t list_elem = { .p = shelf }; 
          list_append(shelves, list_elem);
        }
      elem_t tree_elem = { .p = item };
      elem_t tree_key = { .p = name };
      tree_insert(db, tree_key, tree_elem);
    }
 
  fclose(f);
  return db;
}
