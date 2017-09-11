#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "db.h"

#ifndef __UTILS_H__
#define __UTILS_H__

char *ask_question_shelf(char *question);
double ask_question_float(char *question);
int ask_question_int(char *question);
char *ask_question_string(char *question);
char ask_question_char(char *question);
int read_string(char *buf, int buf_siz);
void print(char *str);
void println(char *str);

#endif
