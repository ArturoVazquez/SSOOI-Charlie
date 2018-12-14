#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>   // Para cambiar permisos de los ficheros
#include <sys/stat.h>    //
#include <sys/wait.h> /** waitpid */
#include <signal.h> /* signal */
#include <time.h>   /* time */
#include <sys/mman.h> /* mmap, munmap */

/* ARGUMENTOS */
#define TAM 20
typedef struct{

	pid_t sigPID;
	pid_t sigAlternative;
	pid_t Charlie,Malo,Bosley,Sabrina,Jill,Kelly;
	int num;

} IAM;

IAM data_process;

int sig, sig_alt; /* Manejadoras */
int fd, tamaño de página;
char * datos;
fd = fopen ("pids.bin", O_RDWR);
tamaño de página = TAM;

void SIGUSR1_Charlie(int); /* Señal que usara Charlie*/
void SIGUSR2_Bosley(int); /*Señal que usara Bosley*/
void SIGALRM_FIN(int); /* Imprimir mensaje si usuario pulsa CTRL_C  o  nuestro programa intenta acceder a una memoria no válida */

void srand (unsigned int); /*Semilla numeros aleatorios*/
void * mmap (NULL, tamaño de página, PROT_EXEC, MAP_SHARED, fd, tamaño de página);/* Proyeccion de memoria a un proceso un archivo*/



int main (int argc, char* argv[]){

	int nombre_incorrecto, demasiados_argumentos, value;
	char nombreInvalido[]="El nombre del ejecutable no es el correcto\n";
	char argumentoInvalido[]="No introduzcas argumentos\n";
   
   
    if(strcmp(argv[0], "./infinito")){
		if(write(1,nombreInvalido,sizeof(nombreInvalido))==-1) return 1;
		return 1;
	}
	
    if(argc>1){
		if(write(1,argumentoInvalido,sizeof(argumentoInvalido))==-1) return 1;
		return 1;
	}
     
    if (chmod("pepe.txt",0666)==-1)    //Funcion de la biblioteca C que comprueba la variable errno y escribe por el canal de
        {char etiqueta[80];             // error estandar del programa una etiqueta que le pasamos como parametro, dos puntos y
              sprintf(etiqueta,"%s:chmod:pepe.txt",argv[0]); //un mensaje indicativo del error que se ha producido
                 perror(etiqueta);
    return 1;
    }






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










int rand (void)  /* para generar sleep Angeles y Malo */
{
    if (void=)
    {
        int a=6,b=12;
            rand=a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1))
         }
        else{
           int a=1,b=3;
              rand=a+(int)(rand()/(1.0+RAND_MAX)*(b-a+1))

    }
}



}