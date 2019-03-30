#include "utils.h"

extern char *strdup(const char *);

answer_t make_float(char *str) {
return (answer_t) { .f = atof(str) };
}

double ask_question_float(char *question) {
// Asks the user for a float and returns it as a float
  return ask_question(question, is_float, make_float).f;
}

bool is_float(char *str) {
  // Determines whether a string is a decimal number or not
  int length = strlen(str);
  bool decimal;
  for (int i=0; i < length; ++i) {
    if (!isdigit(str[i])) {
      if (i == 0 && str[i] == '-') {
        continue;
      }
      if (str[i] == '.' && decimal == false) {
        decimal = true;
        continue;
      }  else {
           return false;
         }
      }
  }
  return decimal;
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


bool not_empty(char *str) {
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
  int buffer = 20;
  char str[20];
  answer_t result;
  do {
    print(question);
    read_string(str, buffer);
    if (!not_empty(str)) {
      continue;
    }
  } while (!check(str));

  result = convert(str);
  return result;
}

int ask_question_int(char *question) {
// Asks the user for an integer and returns it as an int
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i;  // svaret som ett heltal
}

char *ask_question_string(char *question) {
// Asks user for a string and returns it
char *answer = ask_question(question, not_empty, (convert_func) strdup).s;
return answer;
}


int read_string(char *buf, int buf_siz) {
// Stores characters in input buffer at adress of 'buf'
// and returns the length of the string.
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


bool is_number(char *str) {
// Determines whether or not a string is a number

  int length = strlen(str);

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