CC=gcc
FLAGS= -Wall -g

lager: lager.o item.o utils.o list.o tree.o
	$(CC) $(FLAGS) lager.o item.o utils.o list.o tree.o -o lager
lager.o: lager.c item.h utils.h list.h tree.h
	$(CC) $(FLAGS) -c lager.c
utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c
list.o: list.c list.h
	$(CC) $(FLAGS) -c list.c
tree.o: tree.h list.h utils.h tree.c
	$(CC) $(FLAGS) -c tree.c
item.o: item.c list.h
	$(CC) $(FLAGS) -c item.c
run: lager
	./lager
clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f lager
	rm -f *~
.PHONY: lager
