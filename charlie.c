#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>   // Para cambiar permisos de los ficheros
#include <sys/stat.h>    //
#include <sys/wait.h> /** waitpid */
#include <signal.h> /* signal */
#include <time.h>   /* time */
#include <sys/mman.h> /* mmap, munmap */
#include <string.h>


int main (int argc, char* argv[]){

    int rapido = 0;
   /* Entrada argumentos */
    if(argc>2){
		printf("\nHaz introducido demasiados argumentos");
        return 1;
    } else{
        if(argc==2){
            if(!strcmp(argv[1], "rapido")){
            
                rapido = 1;

            }else {
                if(strcmp(argv[1], "normal")){
                    return 1;
                }
            }
        }
    }

    int valor = fork();
    switch (valor)
    {
        case -1:
            perror("prueba");
            exit(1);
            break;
        case 0:
            printf("Soy el hijo\n");
            break;
        default:
            printf("Soy el padre\n");
            break;
    }
    sleep(60);

return 0;
}

void dormirAngeles (int velocidad){
    if(!velocidad){
        // Modo normal
        int a=6,b=12;
        rand=a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1))
        sleep(rand);
    }
}

void dormirMalo (int velocidad){
    if(!velocidad){
        // Modo normal
        int a=1,b=3;
        rand=a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1))
        sleep(rand);
    }
}
