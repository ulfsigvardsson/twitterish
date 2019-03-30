#include <stdio.h>
#include <string.h>

int string_length(char *str);
void print();
void println();

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s words or string", argv[0]);
  }
  else {
    int i;
    printf("puts():\n");
    for (i = 1; i < argc; ++i) {
      puts(argv[i]);
    }
    printf("println():\n");
    for (i = 1; i < argc; ++i) {
      println(argv[i]);
    }
  }
  return 0;
}


int string_length(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

void print(char *str) {
  int length = string_length(str);

  for (int i = 0; i < length; ++i) {
    putchar(str[i]);
  }
}

void println(char *str) {
  print(str);
  putchar('\n');
}
