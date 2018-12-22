#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	pid_t charlie,malo,bosley,sabrina,jill,kelly;
} SOY;

struct sigaction act;
sigset_t mask;
SOY hijos;
char * msg;

void processBosley();
void processCharlie();
void SIGUSR1_CHARLIE(int );

int main (int argc, char* argv[], char * envp []){
    int rapido = 0;
    
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGTERM);
    
    if (strcmp(argv[0],"./charlie") == 0) {
        processCharlie(&hijos);
    }else if(strcmp(argv[0],"bosley") == 0) {
        processBosley(&hijos);
    }

    return 0;
}

void processCharlie(){
    int valor_devuelto;
    hijos.charlie = getpid();

    msg = "\nEJECUTANDO CHARLY...\n";
    write(1, msg , sizeof(&msg) );

    msg = "Soy Charlie\n";
    write(1, msg , sizeof(&msg) -1 );
    
    switch (hijos.bosley = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Bosley\n");
            exit(1);
            break;
        case 0:
            kill(hijos.bosley, SIGUSR2);
            execl("./charlie","bosley", NULL);
            perror("Error al crear al hijo ");
            break;
        default:
            waitpid(hijos.bosley,&valor_devuelto, NULL);
            sigsuspend(&mask);
        break;
    }
    kill(hijos.bosley, SIGUSR1);
    write(1,"\nFIN...\n", 20);
}


void processBosley(){
    int valor_devuelto, s_recibida = 0;
    msg = "CREANDO A BOSLEY...\n";
    write(1, msg, sizeof(msg)-1);
    
    sigsuspend(&mask);
    act.sa_handler = SIGUSR1_CHARLIE;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigaction(SIGUSR1, &act , NULL);

}

void SIGUSR1_CHARLIE(int sigset){
    msg = "SEÑAL RECIBIDA\n";
    write(1, msg , sizeof(msg)-1);
	kill(hijos.charlie, SIGUSR1);
}