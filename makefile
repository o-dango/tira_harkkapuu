harkkatyö: misc.o bintree.o main.o
	gcc misc.o bintree.o main.o -o harkkatyö -Wall -lm
misc.o: misc.c misc.h bintree.h
	gcc misc.c -c -Wall -std=c99 -lm
bintree.o: bintree.c misc.h bintree.h
	gcc bintree.c -c -Wall -std=c99 -lm
main.o: main.c bintree.h misc.h
	gcc main.c -c -Wall -std=c99 -lm
