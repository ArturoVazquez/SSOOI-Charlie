#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h> /** waitpid */
#include <signal.h> /* signal */
#include <time.h>   /* time */
#include <sys/mman.h> /* mmap, munmap */
#include <string.h>
#include <fcntl.h>

#define TAM 20

void dormirMalo (int );
void dormirAngeles (int );
int processBosley();
void processCharlie();
void processMalo();
void processAngel(char *);
void EMPTY_HANDLER(int sigset);
void MANPIUM(int sigset);
int generarRandom(int , int );

int main (int argc, char* argv[], char * envp []){
    int rapido = 0;
    char msg [200];
    if(argc>2){
        sprintf(msg,"\nHaz introducido demasiados argumentos");
        write(1, msg, sizeof(msg)-1);
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
    sigset_t mask;
    sigaddset(&mask, SIGUSR1);       
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_SETMASK, &mask, NULL);   

    if (strcmp(argv[0],"./charlie") == 0) {
        processCharlie();
    }else if(strcmp(argv[0],"bosley") == 0) {
        processBosley();
    }else if(strcmp(argv[0],"sabrina") == 0 || strcmp(argv[0],"kelly") == 0 || strcmp(argv[0],"jill") == 0){
        processAngel(argv[0]);
    }else if(strcmp(argv[0],"malo") == 0){
        processMalo();
    }
    return 0;
}

void processCharlie(){
    struct sigaction act;
    int descript;
    char msg [200] = "";
    pid_t charlie,bosley,malo;
    charlie = getpid();
    sigset_t mask_malo;

    act.sa_handler = EMPTY_HANDLER;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	if(sigaction(SIGUSR1,&act,NULL)==-1){
		perror("SIGACTION USR1");
		exit(1);
	}

    sprintf(msg,"\nSoy Charlie (PID %d) ...", getpid());
    write(1, msg, sizeof(msg)-1);

    sigfillset(&mask_malo);
    sigdelset(&mask_malo, SIGUSR1);
    sigprocmask(SIG_SETMASK, &mask_malo, NULL);  
    
    inicializarArchivo();

    switch (bosley = fork())
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
            sigsuspend(&mask_malo);
            switch (malo = fork())
            {
                case -1:
                    perror("\nNo se ha podido crear al malo\n");
                    exit(1);
                    break;
                case 0:
                    execl("./charlie","malo", NULL);
                    perror("Error al crear al malo ");
                    break;
                default:
                sigsuspend(&mask_malo);

                memset(msg, 0, 200);
                sprintf(msg,"\nCHARLIE : El malo ha nacido (PID %d). Aviso a Bosley", malo);
                write(1, msg, sizeof(msg)-1);
                
                kill(bosley, SIGUSR1); 
                break;
            }
        break;
    }

    sigsuspend(&mask_malo);
    //proyectarFichero(int descript);
    memset(msg, 0, 200);
    sprintf(msg,"\nFIN DEL JUEGO");
    write(1, msg, sizeof(msg)-1);
}

int processBosley(){
    pid_t charlie,jill,kelly,sabrina; //Tengo PID ANGELES
    sigset_t mask_bosley;

    struct sigaction act1;
    int valor_devuelto;
    char msg [200] = "";

    charlie= getppid();

    act1.sa_handler = EMPTY_HANDLER;
	act1.sa_flags = 0;
	sigemptyset(&act1.sa_mask);

	if(sigaction(SIGUSR1,&act1,NULL)==-1){
		perror("SIGACTION USR1");
		exit(1);
	}

    sigfillset(&mask_bosley);
    sigdelset(&mask_bosley, SIGUSR1);
    sigprocmask(SIG_SETMASK, &mask_bosley, NULL);  


    switch (sabrina = fork())
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
            waitpid(sabrina,&valor_devuelto, NULL);
        switch (jill = fork())
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
                waitpid(jill,&valor_devuelto, NULL);
            switch (kelly = fork())
            {
                case -1:
                    perror("\nNo se ha podido crear a Bosley\n");
                    exit(1);
                    break;
                case 0:
                    execl("./charlie","kelly", NULL);
                    perror("Error al crear al hijo ");
                    break;
                default:
                    waitpid(kelly,&valor_devuelto, NULL);
            }
            break;
        }
        break;

    }

    sprintf(msg,"\nBOSLEY : Los Angeles han sido creados!\n");
    write(1, msg, sizeof(msg)-1);

    kill(charlie,SIGUSR1);
    sigsuspend(&mask_bosley);

    memset(msg, 0, 200);
    sprintf(msg,"\nBOSLEY : ATACAR!!!! ANGELES!!!");
    write(1, msg, sizeof(msg)-1);
    kill(sabrina, SIGUSR1);
    kill(kelly, SIGUSR1);
    kill(jill, SIGUSR1);
}

void processAngel(char *angel){
    char msg [200] = "";

    sprintf(msg,"\n%s: Hola, he sido creada ^^ (PID %d)...\n", angel, getpid());
    write(1, msg, sizeof(msg)-1);

    /*
    struct sigaction act4;
  
    act4.sa_handler = EMPTY_HANDLER;
  act4.sa_flags = 0;
  sigemptyset(&act4.sa_mask);

  if(sigaction(SIGUSR1,&act4,NULL)==-1){
    perror("SIGACTION USR1");
    exit(1);
  }
    

    //sigsuspend(); // para atacar empezars
    sigset_t mask_angeles;
    sigfillset(&mask_angeles);
    sigdelset(&mask_angeles, SIGUSR1);
    sigprocmask(SIG_SETMASK, &mask_angeles, NULL);  
  sigsuspend(&mask_angeles);
    int disp=0, fd, dir=0; PID=0;
    char *address;
    fd=open("pids.bin", O_RDWR);
    address = mmap(0, 80, PROT_WRITE | PROT_READ, MAP_SHARED,fd,0);
    close(fd);
    for (disparo=0;disparo<3;disparo++){
    if(strcmp(velocidad,"normal")==0){
      sleep(6+(int)(rand()/(1.0+RAND_MAX)*(12-6+1)));
    }
    dir = generarRandom(0,20);
    PID=address[direccion]*1000+address[direccion+1]*100+address[direccion+2]*10+address[direccion+3];
    //Imprimir por pantalla voy a disparar a PID
    if(PID==0){ 
       //"Pardiez! La pistola se ha encasquillado\"
        if(disparo==2){
          //"He fallado ya tres veces y no me quedan mAs balas. Muero\"
        }
    }else{
      if(0==kill(PID,SIGTERM)){
        //BINGO! He hecho diana! Un malo menos
        if(strcmp(nombre,"KELLY")==0){
          kill(getppid(),SIGTERM);
        }
        if(strcmp(nombre,"SABRINA")==0){
          kill(getppid(),SIGTERM);
        }
        if(strcmp(nombre,"JILL")==0){
          kill(getppid(),SIGTERM);
        }
        munmap(address, 80); 
        exit(0);
      }else{
        if(disparo==2){
          He fallado ya tres veces y no me quedan mAs balas. Muero\"\n",nombre);
        }else{
          //e fallado. Vuelvo a intentarlo
        }
      }
    }
    }
*/
}

void processMalo(){
    pid_t charlie, malo;
    int i=0;
    char msg [200] = "";

    charlie = getppid();
    malo = getpid();

    sprintf(msg,"\nMALO : Me estoy ejecutando muajaja (PID %d)...\n", getpid());
    write(1, msg, sizeof(msg)-1);
    
    
    /******************************************************************************************************************/
    proyeccionMemoria(malo);
    /******************************************************************************************************************/    
    
    while(i<20){  
        dormirMalo(0);
        switch (malo = fork()){
            case -1:
                perror("\nNo se ha podido crear reencarnacion del malo\n");
                exit(1);
                break;
            case 0:
                if (i<1) {
                    kill(charlie, SIGUSR1);
                }
                i++;
                memset(msg, 0, 200);
                sprintf(msg,"JA, JA, JA, me acabo de reencarnar y mi nuevo PID es: %d. Que malo que soy...", getpid());
                write(1, msg, sizeof(msg)-1);
                break;
            default:
                exit(1);
            break;
        }
     }
     
    if (i == 20) {
        memset(msg, 0, 200);
        sprintf(msg,"\nHe sobrevivido a mi vigesima reencarnacion. Hago mutis por el foro\n");
        write(1, msg, sizeof(msg)-1);
        kill(charlie, SIGUSR1);
    }

}

void dormirAngeles (int velocidad){
    if(!velocidad){
        // Modo normal
        int rnd = generarRandom(6,12);
        sleep(rnd);
    }
}

void dormirMalo (int velocidad){
    if(!velocidad){
        // Modo normal
        int rnd = generarRandom(1,3);
        sleep(rnd);
    }
}

void EMPTY_HANDLER(int sigset){
}

/****************************PROYECCIÓN EN MEMORIA***************************/

void inicializarArchivo(){
    int f;
	
	if(-1 == (f =open("pids.bin", O_RDWR | O_CREAT | O_TRUNC, 0600) )){
		perror("error");
		exit(1);
	}
  
	char b[80];

	int i;
	for(i=0; i<80; i++){
		b[i] = 0;
	}

	write(f,b,80);
	close(f);
}

void proyeccionMemoria(pid_t malo){

    int valor,fd,aux,temp,um, dir;
    char *address;

    fd = open("pids.bin", O_RDWR);			
    address = mmap( 0, 80 , PROT_WRITE | PROT_READ , MAP_SHARED, fd , 0);
    close(fd);
    
    do{ 
        dir = generarRandom(0, 20);
    }while( address[dir]!=0 && address[dir+1]!=0 && address[dir+2]!=0 && address[dir+3]!=0 );

    aux = malo%10;
    temp = malo/10;

    address[dir] = aux; 

    aux = temp%10;
    temp = temp/10;

    address[dir+1] = aux;

    aux = temp%10;
    temp = temp/10;
    
    address[dir+2] = aux;
    address[dir+3] = temp;

    munmap(address, 80);
}


/****************************OTRAS FUNCIONES***************************/

int generarRandom(int a, int b){
    return a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1));
}

void MANPIUM(int sigset){
    



    
}
/*NOTAS*/
/* getpid devuelve el identificador de proceso del proceso actual y  getppid  devuelve  el
       identificador de proceso del padre del proceso actual. */
//	fprintf(stderr, "\nPPID: %d|PID: %d",getppid(),getpid());


// void despedida(){
    


//}
