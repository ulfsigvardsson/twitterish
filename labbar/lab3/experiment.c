/*
experiment.c -- 
Written on onsdag, 30 augusti 2017.
*/

#include "utils.h"


// answer_t ask_question(char *question, check_func check, convert_func convert);


int main(int argc, char *argv[]) {
  char question_int[] = "Skriv ett helttal: ";
  int answer_int = ask_question_int(question_int);
  printf("Du skrev: %d\n", answer_int);
  char question_float[] = "Skriv ett decimaltal: ";
  float answer_float = ask_question_float(question_float);
  printf("Du skrev: %f\n", answer_float);
  char *question_string = "Skriv en sträng: ";
  char* answer_string = ask_question_string(question_string);
  printf("Du skrev: %s\n", answer_string);
  return 0;
}

