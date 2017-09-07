#include <stdio.h>
#include <stdlib.h>

void print_number(int num);

int main(int argc, char *argv[])
{
  if (argc !=2)
    {
      printf("Fel antal argument!\n");
      return 0;
    }
  else
    {
      int num = atoi(argv[1]);
      print_number(num);
      

    }
  return 0;
}

void print_number(int num)
{
  
  for (int i = 1; i <= num; ++i)
	{

        if (i%3==0 && i%5==0)
	  {
	    printf("Fizz Buzz");
	  }
        else if (i%3==0)
	  {
	    printf("Fizz");
	  }
	else if (i%5==0)
	  {
	    printf("Buzz");
	  }
	else
	  {
	    printf("%d", i);
	  }
	if (i==num)
	  {
	    printf("\n");
	    break;
	  }
	printf(", ");
        }
}
