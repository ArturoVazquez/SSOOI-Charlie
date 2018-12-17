charlie : charlie.o
	gcc charlie.o -o charlie -lm
charlie.o : charlie.c
	gcc -c charlie.c
