#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <string.h>

#define TAM 20
typedef struct{
	pid_t charlie,malo,bosley,sabrina,jill,kelly;
    int num;
} SOY;

struct sigaction act;

void dormirMalo (int );
void dormirAngeles (int );
void processBosley(SOY *, sigset_t *);
void processCharlie(SOY *, sigset_t *);
void processMalo(SOY *, sigset_t *);
void processAngel(SOY *, char *);


int leerBloque(int * , pid_t, int);
void escribirBloque(int * , pid_t);
void proyectarFichero(int *, int);
void desproyectarFichero(int *, int);


void SIGUSR1_MALO(int sigset, SOY * hijos);
void SIGUSR1_CHARLIE(int , SOY *);
void SIGUSR1_BOSLEY(int , SOY *);


int main (int argc, char* argv[], char * envp []){
    int pid [20];
    int rapido = 0;
    SOY hijos;

    if(argc>2){
		write(1,"\nHaz introducido demasiados argumentos",100);
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
    
    sigset_t mask;/*
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGTERM);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    */
    if (strcmp(argv[0],"./charlie") == 0) {
        processCharlie(&hijos, &mask);
    }else if(strcmp(argv[0],"bosley") == 0) {
        processBosley(&hijos, &mask);
    }else if(strcmp(argv[0],"sabrina") == 0 || strcmp(argv[0],"kelly") == 0 || strcmp(argv[0],"jill") == 0){
        processAngel(&hijos, argv[0]);
    }else if(strcmp(argv[0],"malo") == 0){
        processMalo(&hijos, &mask);
    }

    //sigfillset(&mask); //Volvemos a llenar la mascar

    return 0;
}

void processCharlie(SOY * hijos, sigset_t * mask){
   
    char msg1 [] = "\nEJECUTANDO CHARLY...\n";
    char msg2 [] = "Soy Charlie\n";
    char msg3 [] = "Bosley, hijo de mis entretelas, tu PID es x. Espero a que me avises...\n";
    char msg4 [] = "Veo que los Angeles ya han nacido. Creo al malo...\n";
    char msg5 [] = "El malo ha nacido y su PID es x. Aviso a Bosley\n";

    int valor_devuelto;

    hijos->charlie = getpid();
   
    write(1, msg1 , sizeof(msg1) -1 );
    write(1, msg2 , sizeof(msg2) -1 );
    write(1, msg3 , sizeof(msg3) -1 );
    write(1, msg4 , sizeof(msg4) -1 );
    write(1, msg5 , sizeof(msg5) -1 );

    switch (hijos->bosley = fork())
    {
        case -1:
            perror("\nNo se ha podido crear a Bosley\n");
            exit(1);
            break;
        case 0:
            execl("./charlie","bosley", NULL);
            write(1, msg3 , sizeof(msg3) -1 );
            perror("Error al crear al hijo ");
            break;
        default:
        waitpid(hijos->bosley,&valor_devuelto, NULL);
        write(1, msg2 , sizeof(msg2) -1 );
        switch (hijos->malo = fork())
        {
            case -1:
                perror("\nNo se ha podido crear a Bosley\n");
                exit(1);
                break;
            case 0:                     
                write(1, msg5 , sizeof(msg5) -1 );
                execl("./charlie","malo", NULL);                
                perror("Error al crear al malo ");
                break;
            default:
                write(1, msg4 , sizeof(msg4) -1 );
                act.sa_handler = SIGUSR1_CHARLIE;
                sigemptyset(&act.sa_mask);
                act.sa_flags=0;
                if (-1==sigaction(SIGUSR1,&act,NULL))
                {perror("CHARLIE: sigaction");
                    return 1;}
                wait(&valor_devuelto);
            break;
        }
        break;
    }
}

void processBosley(SOY * hijos, sigset_t * mask){
    act.sa_handler = SIGUSR1_CHARLIE;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act , NULL); 
    sigfillset(mask);
    sigdelset(mask, SIGUSR1);
    
    char msg [] = "\nEJECUTANDO BOSLEY...\n" ;
    char msg1 [] = "Hola, papA, dOnde estA mamA? Mi PID es x y voy a crear a los Angeles...\n" ;
    char msg_correcto [] = "\n He recibido la señal de que el malo se ha creado !" ;
    char msg_angeles [] = "\nLos tres Angeles han acabado su misiOn. Informo del resultado a Charlie y muero\n" ;
    char msg3 [] = "\nPardiez! La pistola se ha encasquillado\n" ;
    char msg4 [] = "\nVoy a disparar al PID x\n" ;
    char msg5 [] = "\nBINGO! He hecho diana! Un malo menos\n" ;
    char msg6 [] = "\nHe fallado. Vuelvo a intentarlo\n" ;
    char msg7 [] = "\nHe fallado ya tres veces y no me quedan mAs balas. Muero\n" ;


        
    
    int valor_devuelto, s_recibida = 0;

    write(1, msg , sizeof(msg)-1);
    write(1, msg1 , sizeof(msg1)-1);
        
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
        waitpid(hijos->sabrina,&valor_devuelto, NULL);
        switch (hijos->jill = fork()){
            case -1:
                perror("\nNo se ha podido crear a Bosley\n");
                exit(1);
                break;
            case 0:
                execl("./charlie","jill", NULL);
                perror("Error al crear al hijo ");
                break;
            default:
                waitpid(hijos->jill,&valor_devuelto, NULL);
                switch (hijos->kelly = fork()){
                    case -1:
                        perror("\nNo se ha podido crear a Bosley\n");
                        exit(1);
                        break;
                    case 0:
                        execl("./charlie","kelly", NULL);
                        perror("Error al crear al hijo ");
                        break;
                    default:
                        act.sa_handler = SIGUSR1_BOSLEY;
                        sigemptyset(&act.sa_mask);
                        act.sa_flags=0;
                        if (-1==sigaction(SIGUSR1,&act,NULL))
                        {perror("CHARLIE: sigaction");
                            return 1;}
                        wait(&valor_devuelto);
                    break;
                }
                break;
        }
        break;
    }
    write(1, msg_angeles , sizeof(msg_angeles)-1);
    kill(hijos->charlie, SIGUSR1);


}

void processAngel(SOY * hijos, char *angel){
    char msg [] = "\nEJECUTANDO ANGEL \n";
    char msg2 [] = "\nHola, he nacido y mi PID es  ...\n" ;
    write(1 , msg2 , sizeof(msg2)-1);
    write(1 , msg , sizeof(msg) - 1);
}

void processMalo(SOY * hijos, sigset_t * mask){
    char msg [] = "\nEJECUTANDO MALO...\n";
    char msg_2 [] = "Soy Malo malisimo\n";
    int i=0, valor_devuelto;

    hijos->malo = getpid();

    write(1, msg , sizeof(msg)-1);
    write(1, msg_2 , sizeof(msg_2)-1);

    act.sa_handler = SIGUSR1_BOSLEY;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if (-1==sigaction(SIGUSR1,&act,NULL))
    {perror("CHARLIE: sigaction");
        return 1;}
    wait(&valor_devuelto);
}

void dormirAngeles (int velocidad){
    if(!velocidad){
        int rnd = generarRandom(6,12);
        sleep(rnd);
    }
}

void dormirMalo (int velocidad){
    if(!velocidad){
        int rnd = generarRandom(1,3);
        sleep(rnd);
    }
}

/*******************************MANEJADORAS**********************************/

void SIGUSR1_CHARLIE(int sigset, SOY * hijos){
	kill(hijos->bosley,SIGUSR1);
    switch(hijos->num){

		case 1:
			
			break;
        case 2:

            break;
        
        case 3:

            break;

        case 4 :

            break;

        case 5 :

            break;

        case 6:

            break;
		default:
			break;
	}
}

void SIGUSR1_MALO(int sigset, SOY * hijos){
    kill(hijos->charlie,SIGUSR1);
}

void SIGUSR1_BOSLEY(int sigset, SOY * hijos){
    kill(hijos->charlie,SIGUSR1);
}

/****************************PROYECCIÓN EN MEMORIA***************************/

void proyectarFichero(int * pids, int file){
    char fichero [] = "PIDS.bin";
    char err_1 [] = "Error al abrir el fichero ";
    char err_2 [] = "Error al proyectar el fichero: en memoria";
    if( -1 == (file = open(fichero, O_RDWR | O_CREAT, 0600)) ) 
        write(1, err_1, sizeof(err_1)-1);

    if( MAP_FAILED == ( pids = (int) mmap(0, sizeof(pids), PROT_READ | PROT_WRITE, MAP_SHARED, file, 0)) ){
        write(1, err_2, sizeof(err_2)-1);
    }

    for(int i = 0; i < sizeof(pids) ; i++){
        pids[i] = 0;
    }
    
}

void escribirBloque(int * pid, pid_t p){
    char err [] = "ERROR: No queda espacio para almacenar mas reencarnaciones (PIDs)";
    int i = generarRandom(0, 19);
    while(pid[i]!=0){
        i = generarRandom(0, 19);
    }
    
    if (i>sizeof(pid)-1) {
        write(1, err, sizeof(err)-1);
    }else{
        pid[i] = p;
    }

}

int leerBloque(int * pid, pid_t p, int num){
    if(pid[num]!= p){
        return 1;
    }
    return 0;
}


void desproyectarFichero(int * pids, int file ){
    char err_1 [] = "ERROR: Hubo problemas des desproyectar el fichero" ;
    char err_2 [] = "ERROR: No se pudo cerrar el fichero" ;
    if(-1 == munmap((void*)pids, sizeof(pids)) ) 
        write(1, err_1, sizeof(err_1)-1);
    if(-1 == close(file) ) 
        write(1, err_2, sizeof(err_2)-1);
}	

/****************************OTRAS FUNCIONES***************************/

int generarRandom(int a, int b){
    return a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1));
}