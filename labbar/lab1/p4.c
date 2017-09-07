#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  if (argc > 3 || argc < 2) {
    printf("Fel antal argument\n");
    return 1;
  }

  else {
    int rows = atoi(argv[1]);
    int growth= atoi(argv[2]);
    int total = 0;
    
    for (int i=1; i<=rows; i++) {
      int fultemp = growth * i;
      
      for (int j=fultemp; j>0; j--) {
	printf("#");
	total += 1;
      }
      
      printf("\n");
    }
    
    printf("Total: %d\n", total);
    return 0;
  }
}

