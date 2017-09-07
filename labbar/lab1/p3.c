#include <stdio.h>

int main(void) {
  int total = 0;
  for (int i=1; i<=10; i++) {
    
    
    for (int j=i; j>0; j--) {
      printf("#");
      total += 1;
    }
    
    printf("\n");

  }
  printf("Total: %d\n", total);
  return 0;
}
