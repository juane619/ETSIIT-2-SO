//servidor

#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

static void mimanejador(int signal){       // Con esto evitamos que queden procesos zombies
  int estado;
  wait(&estado);
  return;
}

static void mimanejador2(int signal){     //manejador para que cuando hagamos control+c borremos los archivos innecesarios
	unlink("bloqueo");


	unlink("comus");
	unlink("comue");

	exit(0);
}

int main(void){
	int fde, fds;

	int pidproxy, pid_leido;
	int leidoe=0, leidos=0;

	if (signal(SIGCHLD, mimanejador) == SIG_ERR)      // Envio de la señal al manejador
		 perror ("Servidor: Error manejando senal");



	//Crear los caucea con nombre (FIFO) si no existe
	umask(0);
	mkfifo("comue",0666);
	mkfifo("comus",0666);

	//Abrir el cauce de entrada para lectura-escritura
	if ( (fde=open("comue",O_RDWR)) <0) {
		 perror("open");
		 exit(-1);
	}

	//Abrir el cauce de salida para lectura-escritura
	if ( (fds=open("comus",O_RDWR)) <0) {
		 perror("open");
		 exit(-1);
	}

	if (open("bloqueo", O_CREAT, 0777) == -1 ){    // Creamos nuestro archivo bloqueo
	  perror("Open fallo");
	}

	if (signal(SIGINT, mimanejador2) == SIG_ERR)      
		 perror ("Servidor: Error manejando senal");

	while(leidoe=read(fde, &pid_leido, sizeof(int))){
		mkfifo("pruebaa",0666);
		if ((pidproxy = fork()) == -1) {
			 perror ("Servidor: Problema al crear proceso proxy");
			 exit(1);
		}

		if (pidproxy == 0 ) {
			int fdf;
			char nombrefifo[25];
			int mipid = getpid();
			sprintf(nombrefifo, "fifo.%d", mipid);
			mkfifo(nombrefifo,0666);
			
			if((leidos=write(fds, &mipid, sizeof(int))<0))
				 perror("Problema write fds.\n");
			
			if ( (fdf=open(nombrefifo,O_RDONLY)) <0) {
				perror("open");
				exit(-1);
			}

			dup2(fdf, STDIN_FILENO);
			if((execlp("./proxy", "proxy", NULL)<0) ){
				perror("\nError en el execl");
				exit(-1);
			}

			exit(0);
		}
	}

	return 0;
}
