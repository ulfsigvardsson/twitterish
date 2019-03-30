#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_number(char *str);
  

int main(int argc, char *argv[]) {
  if (argc == 3) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if (is_number(argv[1]) && is_number(argv[2])) {
      
      while (a>0 && b>0) {
	if (a == b) {
	  printf("Största gemensamma delare är %d\n", a);
	  return 0;
	}
	
	else if (a > b) {
	  a = a-b;
	}
	
	else {
	  b = b-a;
	}
	
      }
    
    }
    
    else {
      printf("Inte heltalsargument.\n");
    }
   
  }
  
  else {
    printf("Fel antal argument.\n");
  }
  
  return 0;
}


bool is_number(char *str) {
  
  int length = strlen(str);
  int i;

  for (i=0; i<length; i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  } 

  return true;
}
