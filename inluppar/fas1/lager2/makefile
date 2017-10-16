CC=gcc
FLAGS= -Wall -g
TESTFLAGS= -Wall -g -fprofile-arcs -ftest-coverage -fPIC

lager: lager.c list.o tree.o item.o utils.o shelfinfo.o
	$(CC) $(FLAGS) $^ -o $@

list.o: list.h list.c
	$(CC) $(FLAGS) list.c -c

tree.o: tree.h tree.c
	$(CC) $(FLAGS) tree.c -c

item.o: list.o item.c
	$(CC) $(FLAGS) item.c list.c -c

utils.o: utils.c
	$(CC) $(FLAGS) utils.c -c

shelfinfo.o: shelfinfo.c shelfinfo.h
	$(CC) $(FLAGS) shelfinfo.c -c

test:	test.c list.o tree.o common.o
	$(CC) $(FLAGS) test.c list.c tree.c common.c -o test -lcunit

analysis: analysis.c list.o tree.o common.o
	$(CC) $(FLAGS) $^ -o $@

run : lager
	./lager test.txt

runtest: test
	./test

valgrind: lager
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./lager test.txt
 
clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f lager
	rm -f *~
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f test
	rm -f gmon.out
