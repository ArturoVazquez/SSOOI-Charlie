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
void dormirMalo (int );
void dormirAngeles (int );

int main (int argc, char* argv[], char * envp []){

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
    int status;
    switch (hijos.bosley = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Bosley\n");
            exit(1);
            break;
        case 0:
            execl("./charlie","bosley", NULL);
            printf("Soy Bosley : %d\n", getpid());
            switch (hijos.sabrina = fork()){
                case -1:
                    perror("\nNo se ha podido crear a Sabrina\n");
                    exit(1);
                    break;
                case 0:
                    execl("./charlie","sabrina", NULL);
                    printf("Soy Sabrina : %d\n", getpid());
                    break;
                default:
                    wait(NULL);
                    switch (hijos.jill = fork()){
                        case -1:
                            perror("\nNo se ha podido crear a Jill\n");
                            exit(1);
                            break;
                        case 0:
                            execl("./charlie","jill", NULL);
                            printf("Soy jill : %d\n", getpid());
                            break;
                        default:
                            wait(NULL);
                            switch (hijos.kelly = fork()){
                                case -1:
                                    perror("\nNo se ha podido crear a Kelly\n");
                                    exit(1);
                                    break;
                                case 0:
                                    execl("./charlie","kelly", NULL);
                                    printf("Soy kelly : %d\n", getpid());
                                    break;
                                default:
                                    wait(NULL);
                                    printf("Soy el padre de kelly: %d\n",  getpid());
                                    break;
                            }
                        break;
                    }
                    break;
            }
        break;     
        default:
            wait(NULL);
            printf("Soy el padre : %d\n",  getpid());
            break;
    }
    sleep(10);
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


/*NOTAS*/
/* getpid devuelve el identificador de proceso del proceso actual y  getppid  devuelve  el
       identificador de proceso del padre del proceso actual.

*/

