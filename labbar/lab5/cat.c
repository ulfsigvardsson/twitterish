#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "db.h"

#define SIZE 16

void cp(char *source, char*dest);
void cat(char *filename, int *row);
void print_menu();
bool is_menu_choice(char c);
char ask_question_menu();
void event_loop(item_t *db, int *db_size, int buf_size);


int main(int argc, char *argv[])
{
  int array_size = SIZE;
  item_t db[SIZE];  // Databas med plats för 16 objekt
  int db_size = 0;
  event_loop(db, &db_size, array_size);
  return 0;
}

// Kopierar en sträng från en pekare till en annan adress
void cp(char *source, char *dest) {
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

void cat(char *filename, int *row)
{
  printf("==== %s ====\n", filename);
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);
  printf("%d. ", *row);
  while (c != EOF)
  { 
    // Om karaktären är newline ökas radräknaren och skrivs
    // ut OM det inte är den sista raden i filen
    if (c == '\n') {
      ++*row;
      fputc(c, stdout);
      c = fgetc(f);
      if (c != EOF) {
        printf("%d. ", *row);
      }
    }
    else {
      fputc(c, stdout);
      c = fgetc(f);
    }
  }
  fclose(f);
}

void print_menu() {
  char *menu =
    "[L]ägga till en vara\n"\
    "[T]a bort en vara\n"\
    "[R]edigera en vara\n"\
    "Ån[g]ra senaste ändringen\n"\
    "Lista [h]ela varukatalogen\n"\
    "[A]vsluta\n\n";
  printf("%s", menu);
}

char ask_question_menu() {
  char choice = ask_question_char("Ange ett menyval: ");

  while (!is_menu_choice(choice)) {
     print_menu();
     choice = ask_question_char("Ange ett menyval: ");
  }
  return choice;
}

bool is_menu_choice(char c) {
  char s = toupper(c);
  char *choices = "LTRGHA";
  for (int i = 0; i < strlen(choices); ++i) {
    if (s == choices[i]) {
      return true;
    }
  } 
  return false;
}


void event_loop(item_t *db, int *db_size, int buf_size) {
  char choice;
  do {
    print_menu();
    choice = toupper(ask_question_menu());
    printf("Du valde %c\n", choice);
    if (choice == 'L') {
      add_item_to_db(db, db_size, buf_size);
    }
    else if (choice == 'T') {
      remove_item_from_db(db, db_size, buf_size);
    }
    else if (choice == 'R') {
      edit_db(db, *db_size);
    }
    else if (choice == 'G') {
      printf("Not yet implemented!\n");
    }
    else if (choice == 'H') {
      list_db(db, *db_size);
    }
  } while (choice != 'A');
}
