harkkatyö: misc.o bintree.o main.o print.o
	gcc misc.o bintree.o print.o main.o -o harkkatyö -Wall -lm
misc.o: misc.c misc.h bintree.h print.h
	gcc misc.c -c -Wall -ansi -std=c99 -lm
bintree.o: bintree.c misc.h bintree.h print.h
	gcc bintree.c -c -Wall -ansi -std=c99 -lm
print.o: print.c misc.h bintree.h
	gcc print.c -c -Wall -ansi -std=c99 -lm
main.o: main.c bintree.h misc.h print.h
	gcc main.c -c -Wall -ansi -std=c99 -lm
