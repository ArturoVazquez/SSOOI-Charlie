#include <stdio.h>
#include <unistd.h>

int main (void){
    int valor = fork();
    switch (valor)
    {
        case -1:
            perror("prueba");
            exit(1);
            break;
        case 0:
            printf("Soy el hijo");
            break;
        default:
            printf("Soy el padre");
            break;
    }
    sleep(60);
}