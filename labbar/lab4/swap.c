/*
swap.c -- 
Written on torsdag, 31 augusti 2017.
*/

#include <stdio.h>
#include <stdlib.h>

struct point
{
  int x;
  int y;
};

int main(int argc, char *argv[]) {
  int x = 7;
  int y = 42;
  swap(&x, &y);
  printf("%d, %d\n", x, y);
  print("Testar\n");
  struct point p = { .x = 10, .y = -42};
  printf("point(x=%d,y=%d)\n", p.x, p.y);
  return 0;
}

void swap(int *a, int *b) {
  int temp1 = *a;
  int temp2 = *b;
  a = temp2;
  b = temp1;
}

void print(char *str) {
  for (; *str !='\0'; str++) {
    putchar(*str);
  }
}
