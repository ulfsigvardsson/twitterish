#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#ifndef __UTILS_H__
#define __UTILS_H__




typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

typedef union {
  int   i;
  float f;
  char *s;
} answer_t;

answer_t ask_question(char *question, check_func check, convert_func convert);
double ask_question_float(char *question);
int ask_question_int(char *question);
char *ask_question_string(char *question);
bool is_float(char *str);
bool is_number(char *str);
void clear_input_buffer();
bool not_empty(char *str);
int read_string(char *buf, int buf_siz);
void print(char *str);
void println(char *str);
answer_t make_float(char *str);
#endif
