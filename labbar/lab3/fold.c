/*
fold.c -- implementation of fold
Written on onsdag, 30 augusti 2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include "/home/ulf/Datavetenskap/IOOOPM/lab2/utils.h"

typedef int(*int_fold_func)(int, int);

int sum(int numbers[], int numbers_siz);
int add(int a, int b);

int main(int argc, char *argv[])
{
  int arr_int[5] = {1, 2, 3, 4, 5};
  int arr_size = 5;
  int result = sum(arr_int, arr_size);
  printf("Summan av [");
  for (int i = 0; i < arr_size; ++i) {
    printf("%d, ", arr_int[i]);
  }
  printf("] är: %d\n", result);
}

/// En funktion som tar en array av heltal, arrayens längd och
/// en pekare till en funktion f av typen Int -> Int -> Int
int foldl_int_int(int numbers[], int numbers_siz, int_fold_func f) {
  int result = 0;

  // Loopa över arrayen och för varje element e utför result = f(result, e)
  for (int i = 0; i < numbers_siz; ++i) {
    result = f(result, numbers[i]);
  }
  return result;
}


int sum(int numbers[], int numbers_siz) {
  int result = 0;
  result = foldl_int_int(numbers, numbers_siz, add);
  return result;
}


int add(int a, int b) {
  return a + b;
}
