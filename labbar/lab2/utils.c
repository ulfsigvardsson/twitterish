#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include <string.h>
#include <ctype.h>

float ask_question_float(char *question) {
  // Asks the user for a float and returns it as a float
}

bool is_float(char *str) {
  // Determines whether a string is a decimal number or not
  int length = strlen(str);
  bool valid;
  bool decimal;
  // If the first character is not a digit the function checks to see if
  // it is the minus sign.
  if (!isdigit(str[0])) {
      if (str[0] != '-') {
         return false;  // If it is not it's not a number
      }
  } 
  for (int i=1; i < length; i++) {
    // If the first character is a digit or the minus sign,
    // the rest of the string is evaluated.

    if (!isdigit(str[i])) {
      if (str[i] == '.') {
        if (decimal == true) {
          return false;
	}
        else {
          decimal = true;
	}
      }
    }
  }
  return true;
}


void clear_input_buffer() {
  // Clears input buffer
  int c;
  do {
    // Pops next character from input buffer and assign it to 'c'
    c = getchar();
  }
  // If next character is '\n' the string has ended
  // and no more characters need to be flushed, otherwise
  // the next character in the buffer is flushed.
  while (c != '\n' && c != EOF); 
  putchar('\n');
}



int ask_question_int(char *question)
// Asks the user for an integer and returns it as an int
{
  char num[10];
  do {
    printf("%s\n", question);
    read_string(num, 10);  // Stores input in 'num', max 10 digits.
    if (!is_number(num)) {
      printf("Inte ett nummer!\n\n");
    }      
  }
  // If no items are read or if input is faulty, the loop repeats itself.
  while (strlen(num) == 0 || !is_number(num)); 
  // The number inputed by the user is converted and returned
  return atoi(num);
}


int read_string(char *buf, int buf_siz)
// Stores characters in input buffer at adress of 'buf'
// and returns the length of the string.
{
  char c;
  int charcount = 0;
  
  for (int i = 0; i < buf_siz; ++i) {
    // Pops next character in buffer
    c = getchar();
    if (c == '\n' || c == EOF) {
      // If string has ended the next character is set to '\0'.
      buf[i] = '\0';
      return charcount;
    }
    if (charcount >= buf_siz) {
      // If the string is longer than the allowed buffer size
      // the remainder of the buffer is flushed.
      clear_input_buffer();
      return charcount;
    }
    else {
      buf[i] = c;
      ++charcount;
    }
  }
  return charcount;
}


char *ask_question_string(char *question, char *buf, int buf_siz)
// Asks user for a string and returns it
{
  int read;
  
  do {
      printf("%s\n", question);
      // 'read' is number of read characters,
      // 'read_string' stores user input into adress of 'buf'.
      read = read_string(buf, buf_siz);
     }
  // If no input is given the loop repeats.
  while (read == 0);
  // The inputed string is returned
  return buf;
}


bool is_number(char *str) {
// Determines whether or not a string is a number

  int length = strlen(str);
  bool valid;

  // If the first character is not a digit the function checks to see if
  // it is the minus sign.
  if (!isdigit(str[0])) {
      if (str[0] != '-') {
         return false;  // If it is not it's not a number
      }
  } 
  for (int i=1; i < length; i++) {
    // If the first character is a digit or the minus sign,
    // the rest of the string is evaluated.

    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

void print(char *str) {
  int length = strlen(str);

  for (int i = 0; i < length; ++i) {
    putchar(str[i]);
  }
}

void println(char *str) {
  print(str);
  putchar('\n');
}
