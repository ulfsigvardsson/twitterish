#include <stdio.h>

void cp(char *source, char*dest)
{
  
  FILE *s = fopen(source, "r");
  FILE *d = fopen(dest, "w");
  int c = fgetc(s);
 
  while (c != EOF) {
    fputc(c, d);
    c = fgetc(s);
  }
  fclose(s);
  fclose(d);
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else {
    cp(argv[1], argv[2]);
  }

  return 0;
}
