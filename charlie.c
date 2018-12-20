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

	pid_t malo,bosley,sabrina,jill,kelly;

} SOY;

void dormirMalo (int );
void dormirAngeles (int );
int processBosley(SOY *);
void processCharlie(SOY *);
void processMalo(SOY *);
void processAngel(SOY *, char *);

int main (int argc, char* argv[], char * envp []){
    int rapido = 0;
    SOY hijos;

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

  //CREO MASCARA
/*
    sigdelset(&mask,SIGTERM);
    sigset_t mask;
    sillfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask,SIGTERM);
    sigprocmask(SIG_SETMASK, &mask, NULL);
*/
    if (strcmp(argv[0],"./charlie") == 0) {
        processCharlie(&hijos);
    }else if(strcmp(argv[0],"bosley") == 0) {
        processBosley(&hijos);
    }else if(strcmp(argv[0],"sabrina") == 0 || strcmp(argv[0],"kelly") == 0 || strcmp(argv[0],"jill") == 0){
        processAngel(&hijos, argv[0]);
    }else if(strcmp(argv[0],"malo") == 0){
        processMalo(&hijos);
    }
    return 0;
}

void processCharlie(SOY * hijos){
    pid_t charlie;
    charlie = getpid();

    printf("\nEJECUTANDO CHARLY...\n");
    printf("Soy Charlie : %d\n", charlie);

    switch (hijos->bosley = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Bosley\n");
            exit(1);
            break;
        case 0:
            execl("./charlie","bosley", NULL);
            perror("Error al crear al hijo ");
            break;
        default:
            switch (hijos->malo = fork())
            {
                case -1:
                    perror("\nNo se ha podido crear a Bosley\n");
                    exit(1);
                    break;
                case 0:
                    execl("./charlie","malo", NULL);
                    perror("Error al crear al malo ");
                    break;
            }
        break;
    }
    // SIGACTION DE CHARLIE AQUI
    /*
    sigaction()
    */
    // 3 SIGSUSPEND SOBRE LA MASCARA CREADA PORQUE CADA ANGEL ENVIA UNA SEÑAL (ESPERA X 3 SEÑALES)CUANDO SE DESBLOQUEA ES XQ YA SE HAN CREADO LOS 3 ANGELES
    sleep(90);
    printf("\nFIN...\n");
}

int processBosley(SOY * hijos){
    printf("\nEJECUTANDO BOSLEY...\n");
    printf("Soy Bosley es %d\n", getpid());
    
    switch (hijos->sabrina = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Sabrina\n");
            exit(1);
            break;
        case 0:
            execl("./charlie","sabrina", NULL);
            perror("Error al crear al hijo ");
            break;
        default:
        switch (hijos->jill = fork())
        {
            case -1:
                perror("\nNo se ha podido crear a Bosley\n");
                exit(1);
                break;
            case 0:
                execl("./charlie","jill", NULL);
                perror("Error al crear al hijo ");
                break;
            default:
            switch (hijos->kelly = fork())
            {
                case -1:
                    perror("\nNo se ha podido crear a Bosley\n");
                    exit(1);
                    break;
                case 0:
                    execl("./charlie","kelly", NULL);
                    perror("Error al crear al hijo ");
                    break;
            }
            sleep(10);
            break;
        }
        sleep(10);
        break;

    }
    printf("\nTODOS LOS ANGELES CREADOS\n");
    sleep(20);
        //CREAR SIGACTION BOSLEY
}

void processAngel(SOY * hijos, char *angel){
    printf("\nEJECUTANDO ANGEL... %s\n", angel);
    sleep(15);
        //AQUI SIGACTION ANGELES
}

void processMalo(SOY * hijos){
    printf("\nEJECUTANDO MALO...\n");
        //SIGACTION DE MALO

    int i=0;
    hijos->malo = getpid();
    printf("Soy Malo malisimo : %d\n",  getpid());
    /*
    while(i<20){  
        dormirMalo(0);
        switch (hijos->malo=fork()){
            case -1:
                perror("\nNo se ha podido crear reencarnacion del malo\n");
                exit(1);
                break;
            case 0:
                kill(hijos->malo, SIGKILL);
                hijos->malo = getpid();
                if(i=0){
                kill(Charlie)    //Mensaje a charlie muerte del primer malo
                }
                i++;
                printf("JA, JA, JA, me acabo de reencarnar y mi nuevo PID es: %d. Que malo que soy...",hijos->malo);
                break;
        }
     }
     
     if (i == 20) {
         printf("\nHe sobrevivido a mi vigesima reencarnacion. Hago mutis por el foro\n");
     }*/
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

/* Proyeccion de memoria a un proceso un archivo
void * mmap (NULL, tamaño de página, PROT_EXEC, MAP_SHARED, fd, 0){  
    for(int i=0,i<TAM;i++){
        &i=0;
    }
} */


/*NOTAS*/
/* getpid devuelve el identificador de proceso del proceso actual y  getppid  devuelve  el
       identificador de proceso del padre del proceso actual.

*/

