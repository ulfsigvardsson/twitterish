/*
db.c -- database
Written on fredag,  1 september 2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"

extern char *strdup(const char *);

struct item {
  char *name;
  char *descr;
  int price;
  char *shelf;
};

typedef struct item item_t;

void print_item(item_t *item);
item_t make_item(char *name, char *descr, int price, char *shelf);
item_t input_item();
char *ask_question_shelf(char *question);
bool is_valid_shelf(char *str);
int add_to_string(char *arr[], char *buf, int index);
char *magick(char *arr1[], char *arr2[], char *arr3[]);
int add_to_string(char *arr[], char *buf, int index);
void list_db(item_t *items, int no_items);
void edit_db(item_t *items, int no_items);


  
int main(int argc, char *argv[]) {
  srand(time(NULL));
  
  char *array1[] = { "Laser", "Extra", "Polka", "Äppel", "Över"};
  char *array2[] = { "förnicklad", "smakande", "ordinär", "dragerad","dragen" };
  char *array3[] = { "skruvdragare", "kola","uppgift" , "spegel", "mobil" };
  
  if (argc < 2) {
    printf("Usage: %s number\n", argv[0]);
  }
  else {
    item_t db[16];   // Array med plats för 16 varor
    int db_siz = 0;    // Antalet varor i arrayen just nu

    int items = atoi(argv[1]);  // Antalet varor som skall skapas

    if (items > 0 && items <= 16) {
      for (int i = 0; i < items; ++i) {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else {
      puts("Sorry, must have [1-16] items in database.");
      return 1;  // Avslutar programmet!
    }
    
    for (int i = db_siz; i < 16; ++i) {
        char *name = magick(array1, array2, array3);  /// Lägg till storlek
        char *desc = magick(array1, array2, array3);  /// Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',  // Hur funkar detta??
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
    list_db(db, db_siz);
    edit_db(db, db_siz);
  }
  return 0;
}

void print_item(item_t *item) {
  int kronor = (item->price)/100;
  int oren   = (item->price)%100;
  printf("Name: %s\n", item->name);
  printf("Desc: %s\n", item->descr);
  printf("Price: %d.%d SEK\n", kronor, oren);
  printf("Shelf: %s\n", item->shelf);
}

item_t make_item(char *name, char *descr, int price, char *shelf) {
  item_t item ={ .name = name, .descr = descr, .price = price, .shelf = shelf };
  return item;
}

item_t input_item() {
  char *name  = ask_question_string("Ange namn på vara\n");
  char *descr = ask_question_string("Ange en beskrivning av varan\n");
  int price   = ask_question_int("Ange pris på varan\n");
  char *shelf = ask_question_shelf("Ange hyllplats\n");
  item_t item = make_item(name, descr, price, shelf);
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
  for (int i = 0; i < no_items; ++i) {
    item = items[i];
    name = item.name;
    printf("%d: %s\n" , i+1, name);
  }
}

void edit_db(item_t *items, int no_items) {
  int num;

  do {
    num = ask_question_int("Ange index för varan du vill ersätta\n");
  } while (num < 1 || num > no_items);
  
  print_item(&items[num-1]);  // Hur kan jag skapa en variabel av items[num-1] och skriva till rätt adress?

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
      char *new_shelf = ask_question_string("Ange ny hylla\n");
      items[num -1].shelf = new_shelf;
      break;
    }
  }
  list_db(items, no_items);
}
