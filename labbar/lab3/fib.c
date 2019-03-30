#include <stdio.h>
#include <stdlib.h>

int fib(int num);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No input.\n");
    return 0;
  }
  int num = atoi(argv[1]);
  int fib_no = fib(num);
  printf("The %dth Fibonacci number is %d\n", num, fib_no);
  return 0;
}

int fib(int num) {
  if (num == 0 || num == 1) {
    return 1;
  }
  return fib(num-1) + fib(num-2);
}
