main: lager.o db.o utils.o list.o tree.o
	gcc -g lager.o db.o utils.o list.o tree.o -o lager -lcunit
lager.o: lager.c db.h utils.h list.h tree.h
	gcc -c -g -Wall lager.c
db.o: db.c db.h utils.h
	gcc -c -g -Wall db.c
utils.o: utils.c db.h utils.h
	gcc -c -g -Wall utils.c
list.o: list.c list.h db.h
	gcc -c -g -Wall list.c
tree.o: tree.h list.h utils.h db.h
	gcc -c -g -Wall tree.c
