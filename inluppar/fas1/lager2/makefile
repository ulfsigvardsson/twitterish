CC=gcc
FLAGS= -Wall -g

lager: lager.c list.o tree.o
	$(CC) $(FLAGS) $^ -o $@

list.o: list.h list.c
	$(CC) $(FLAGS) list.c -c

tree.o: tree.h tree.c
	$(CC) $(FLAGS) tree.c -c

test:	test.c list.o tree.o common.o
	$(CC) $(FLAGS) test.c list.c tree.c common.c -o test -lcunit

runtest: test
	./test

valgrind: lager.o
	valgrind --leak-check=full ./lager

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f lager
	rm -f *~
