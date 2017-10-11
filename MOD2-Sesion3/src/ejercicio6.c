//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
pid_t pid;
int estado;

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(-1);
}
else if(pid==0) {  //proceso hijo ejecutando el programa
	if( (execl("/usr/bin/ldd","ldd","ej66", NULL)<0)) {
		perror("\nError en el execl");
		exit(-1);
	}
}
wait(&estado);
printf("\nMi hijo %d ha finalizado con el estado %i\n",pid,estado>>8);

/*En caso de que el programa ldd se ejecute sin problemas, se guardara en la variable estado el codigo 0(devuelto por el hijo). 
Devolvera en la variable estado el codigo devuelto por el hijo(que en este caso es el execl) aunque en realidad, este estado de finalizacion
lo guarda en el segundo byte, por eso lo movemos hacia la izquierda un byte*/

exit(0);

}
