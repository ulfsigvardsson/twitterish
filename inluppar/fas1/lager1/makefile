CC=gcc
FLAGS= -Wall -g

lager: lager.o db.o utils.o list.o tree.o
	$(CC) $(FLAGS) lager.o db.o utils.o list.o tree.o -o lager
lager.o: lager.c db.h utils.h list.h tree.h
	$(CC) $(FLAGS) -c lager.c
db.o: db.c db.h list.h utils.h
	$(CC) $(FLAGS) -c db.c
utils.o: utils.c db.h utils.h
	$(CC) $(FLAGS) -c utils.c
list.o: list.c list.h db.h
	$(CC) $(FLAGS) -c list.c
tree.o: tree.h list.h utils.h db.h tree.c
	$(CC) $(FLAGS) -c tree.c
run: lager
	./lager
.PHONY: lager
