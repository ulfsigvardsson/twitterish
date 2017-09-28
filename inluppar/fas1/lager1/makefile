CC=gcc
FLAGS= -Wall -g -I/usr/local/Cellar/cunit/2.1-3/include -L/usr/local/Cellar/cunit/2.1-3/lib


lager: lager.o 
	$(CC) $(FLAGS) lager.o saveinfo.o item.o utils.o list.o tree.o -o lager
tester: tester.o 
	$(CC) $(FLAGS) tester.o saveinfo.o item.o utils.o list.o tree.o -o tester -lcunit 
tester.o: tester.c item.o utils.o list.o tree.o saveinfo.o
	$(CC) $(FLAGS) -c tester.c -lcunit
lager.o: lager.c item.o utils.o list.o tree.o saveinfo.o
	$(CC) $(FLAGS) -c lager.c
utils.o: utils.c utils.h
	$(CC) $(FLAGS) -c utils.c
list.o: list.c list.h
	$(CC) $(FLAGS) -c list.c
tree.o: tree.h list.o utils.o tree.c
	$(CC) $(FLAGS) -c tree.c
item.o: item.c list.h
	$(CC) $(FLAGS) -c item.c
saveinfo.o: saveinfo.c saveinfo.h
	$(CC) $(FLAGS) -c saveinfo.c
run: lager
	./lager
clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f lager
	rm -f *~
.PHONY: lager tester


