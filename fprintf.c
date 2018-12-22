#include<stdio.h>
#include <unistd.h>
#include <string.h>

void imprimirPantalla(char *);
int main() 
{ 
    char str[50]; 
    char * print;
    sprintf(print,"EL PROCESO TIENE PID : %d", getpid()); 
    strcat(print,"\0");
    write(1 , print, sizeof(print)-1);
    return 0; 
}
