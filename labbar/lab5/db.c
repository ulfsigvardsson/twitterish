/*
db.c -- database
Written on fredag,  1 september 2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "db.h"


void print_item(item_t *item);

void print_item(item_t *item) {
  int kronor = (item->price)/100;
  int oren   = (item->price)%100;
  printf("Name: %s\n", item->name);
  printf("Desc: %s\n", item->descr);
  printf("Price: %d.%d SEK\n", kronor, oren);
  printf("Shelf: %s\n", item->shelf);
  printf("Amount: %d\n", item->amount);
}

item_t make_item(char *name, char *descr, int price, char *shelf, int amount) {
  item_t item ={ .name = name, .descr = descr, .price = price, .shelf = shelf, .amount = amount };
  return item;
}

item_t input_item() {
  char *name  = ask_question_string("Ange namn på vara: \n");
  char *descr = ask_question_string("Ange en beskrivning av varan: \n");
  int price   = ask_question_int("Ange pris på varan: \n");
  char *shelf = ask_question_shelf("Ange hyllplats: \n");
  int amount  = ask_question_int("Ange antal varor: \n");
  item_t item = make_item(name, descr, price, shelf, amount);
  return item;
}

char *ask_question_shelf(char *question) {
  char *answer;
  answer = ask_question(question, is_valid_shelf, (convert_func) strdup).s;
  return answer;
  }

bool is_valid_shelf(char *str) {
// Determines whether or not a string is a valid shelf number
  int length = strlen(str);
  for (int i=0; i < length; ++i) {
    if (i == 0) {
      if (!isupper(str[i])) {
         return false;
      }
    }
    // If the first character is valid,
    // the rest of the string is evaluated.
    else {
      if (!isdigit(str[i])) {
        return false;
      }
    }
  }
  return true;
}

char *magick(char *arr1[], char *arr2[], char *arr3[]) {
  char buf[255];
  int index = 0;
  index = add_to_string(arr1, buf, index);
  buf[index] = '-';
  ++index;
  index = add_to_string(arr2, buf, index);
  buf[index] = ' ';
  ++index;
  index = add_to_string(arr3, buf, index);
  buf[index] = '\0';
  return strdup(buf);
}

int add_to_string(char *arr[], char *buf, int index) {
  int max      = 5;  // samma längd på alla arrays
  int rand_num = random() %max;
  char *word   = arr[rand_num];

  for (int j = 0; j < strlen(word); ++j) {
    buf[index] = word[j];
    ++index;
  }
  return index;
}

void list_db(item_t *items, int no_items) {
  char *name;
  item_t item;
  printf("\n====DATABAS====\n");
  for (int i = 0; i < no_items; ++i) {
    item = items[i];
    name = item.name;
    printf("%d: %s\n" , i+1, name);
  }
  printf("\n");
}

void edit_db(item_t *items, int no_items) {
  int num;
  list_db(items, no_items);
  do {
    num = ask_question_int("Ange index för varan du vill ersätta\n");
  } while (num < 1 || num > no_items);
  
  print_item(&items[num-1]);

  while (true) {
    char *choice = ask_question_string("Ange vilken del du vill ersätta\n");
    if (strcmp("Name", choice) == 0) {
      char *new_name = ask_question_string("Ange nytt namn\n");
      items[num -1].name = new_name;
      break;
    }
    else if (strcmp("Desc", choice) == 0) {
      char *new_desc = ask_question_string("Ange ny beskrivning\n");
      items[num -1].descr = new_desc;
      break;
    }  
    else if (strcmp("Price", choice) == 0) {
      int new_price = ask_question_int("Ange nytt pris\n");
      items[num -1].price = new_price;
      break;
    }
    else if (strcmp("Shelf", choice) == 0) {
      char *new_shelf = ask_question_shelf("Ange ny hylla\n");
      items[num -1].shelf = new_shelf;
      break;
    }
     else if (strcmp("Amount", choice) == 0) {
      int new_amount = ask_question_int("Ange nytt antal\n");
      items[num -1].amount = new_amount;
      break;
     }
  }
}

void add_item_to_db(item_t *db, int *db_size, int buf_size) {
  item_t new_item = input_item();
  if (*db_size < buf_size) {
    ++(*db_size);
    db[*db_size-1] = new_item;
  }
}

void remove_item_from_db(item_t *db, int *db_size, int buf_size) {
  list_db(db, *db_size);
  int num;
  do {
    num = ask_question_int("Ange index för varan du vill ta bort\n");
  } while (num < 1 || num > *db_size);

  for (int i = num -1; i < *db_size-1; ++i) {
    db[i] = db[i+1];
  }
  --(*db_size);
}
