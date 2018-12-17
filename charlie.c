#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> /** waitpid */
#include <signal.h> /* signal */
#include <time.h>   /* time */
#include <sys/mman.h> /* mmap, munmap */
#include <string.h>

#define TAM 20
typedef struct{

	pid_t sigPID;
	pid_t sigAlternative;
	pid_t malo,bosley,sabrina,jill,kelly;
	int num;

} SOY;

int main (int argc, char* argv[]){

    int rapido = 0;
    pid_t charlie;
    SOY hijos;
    
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

    charlie = getpid();
    printf("Soy Charlie : %d\n", charlie);

    switch (hijos.bosley = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Bosley\n");
            exit(1);
            break;
        case 0:
            printf("Soy Bosley : %d\n", getpid());
            //crearAngeles(*hijos);
            switch (hijos.sabrina = fork()){
                case -1:
                    perror("\nNo se ha podido crear a Sabrina\n");
                    break;
                case 0:
                    printf("Soy Sabrina : %d\n", getpid());
                    break;
                default:
                    printf("Soy el padre de sabrina: %d\n", getppid());
                    break;
            }

            switch (hijos.sabrina = fork()){
                case -1:
                    perror("\nNo se ha podido crear a Sabrina\n");
                    break;
                case 0:
                    printf("Soy jill : %d\n", getpid());
                    break;
                default:
                    printf("Soy el padre de jill: %d\n",  getppid());
                    break;
            }

            switch (hijos.sabrina = fork()){
                case -1:
                    perror("\nNo se ha podido crear a Sabrina\n");
                    break;
                case 0:
                    printf("Soy kelly : %d\n", getpid());
                    break;
                default:
                    printf("Soy el padre de kelly: %d\n",  getppid());
                    break;
            }
            break;
        default:
            printf("Soy el padre : %d\n",  getppid());
            break;
    }
    sleep(60);
return 0;
}


void dormirAngeles (int velocidad){
    if(!velocidad){
        // Modo normal
        int a=6,b=12, rnd;
        rnd = a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1));
        sleep(rnd);
    }
}

void dormirMalo (int velocidad){
    if(!velocidad){
        // Modo normal
        int a=1,b=3, rnd;
        rnd = a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1));
        sleep(rnd);
    }
}
