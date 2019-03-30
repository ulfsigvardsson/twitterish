#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[])
{
  // nollställer tick-tiden så att vi får nya slumptal
  srand(time(NULL));
  // slumptal 0-1023
  int answer = random() %1024;
  // allokerar plats för 15 karaktärer för namnet inkl. '\0'
  char user_name[15];
  int guess_count = 0;
  int current_guess;

  // returvärdetfrån ask_question_string används inte för
  // stunden och kastas därför bort.
  // ask_question_string ändrar på user_name eftersom den får adressen
  ask_question_string("Vad heter du?", user_name, 15);  .
  printf("Du %s, jag tänker på ett tal. Kan du gissa vilket?\n", user_name);

  do {
     if (guess_count >= 15) {
       printf("Nu har du slut på gissningar! Jag tänkte på %d\n",  answer);
       return 0;
     }
     current_guess = ask_question_int("Gissa ett tal: ");
     if (current_guess >  answer {
       printf("För högt!\n");
     } else if (current_guess <  answer) {
       printf("För lågt!\n");
     }
     ++guess_count;
    }
    // Om gissningen är fel upprepas loopen
    while (current_guess !=  answer);
  printf("Det tog %d gissningar att komma fram till %d\n", guess_count, answer);
  return 0;
}

