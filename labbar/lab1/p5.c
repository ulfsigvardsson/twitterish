#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    printf("Fel antal argument\n");
    return 1;
  }

  else {

    int num = atoi(argv[1]);
    int i;
    int j;
    int bool = 1;
    
    for (i=2; i<num; i++){
      for (j=2; j<num; j++){
	if (i*j == num){
	  bool = 0;
	  printf("Not a prime number.\n");
	  return 0;
	}
      }
    }

    printf("Prime number\n");
    return 0;
    
  }
}

