charly : charly.o
	gcc charly.o -o charly -lm
charly.o : charly.c
	gcc -c charly.c
