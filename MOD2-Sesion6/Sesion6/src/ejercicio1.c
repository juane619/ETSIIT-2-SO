/*
Ejercicio1: redireccionar entrada o salida estandar de un programa con fcntl.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <string.h>

int main(int argc, char *argv[]){
if(argc < 4){
		printf("Error en la ejecucion del programa. Uso: orden <o> nombre_archivo");
		exit(-1);
}

	int fd_to_close;
	int fd = open(argv[3], O_WRONLY|O_CREAT, 0777);
	//printf("NO Entrando en <");

	if(!(strcmp(argv[2], "<"))){
		printf("Entrando en <");
		fd_to_close= 0;
		close(fd_to_close);
		if(fcntl(fd, F_DUPFD, fd_to_close) == -1 ) 
			perror ("Fallo en fcntl");
		execlp(argv[1],argv[1],argv[3], NULL);
	}
	else if(!(strcmp(argv[2], ">"))){
		printf("Entrando en >");
		fd_to_close= 1;
		close(fd_to_close);

		if(fcntl(fd, F_DUPFD, fd_to_close) == -1 ) 
			perror ("Fallo en fcntl");
		
		execlp(argv[1],argv[1],NULL);
	}

	
	exit(0);
}
