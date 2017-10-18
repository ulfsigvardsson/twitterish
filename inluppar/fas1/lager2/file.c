#include "file.h"
#include "item.h"
#include "list.c"
#include "common.h"
#include "tree.h"
#include <stdio.h>


int db_size(FILE *f)
{
  int size = 0;
  fscanf(f, "%d\n", &size);
  return size;
}



int load_db(char *path)
{
  FILE *f = fopen(path, "r");
  char name[20], descr[100];
  int price, shelf_count; 
  int size = db_size(f); 
    
  for (int i = 0; i < size; ++i) 
    {
                       fgets(name, 20, f);
                       fgets(descr, 100, f); // Beskrivningen är troligtvis flera ord, därav fgets() 
                       fscanf(f, "%d ", &price);
      fscanf(f, "%d ", &shelf_count);

      printf("Namn: %s", name);
      printf("Beskrivning: %s", descr);
       printf("Pris: %d\n", price);
       printf("Hylla\tAntal\n");
      
       char id[3];
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


int main(int argc, char *argv[])
{
  load_db(argv[1]);
  return 0;
}
