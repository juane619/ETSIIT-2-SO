//tarea5.c
//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{

if(argc<2){
   perror("\nDebes especificar al menos un argumento(nombre del programa y sus argumentos si los tiene).");
	exit(-1);
}

int n_args= argc-2;
const char* arguments[n_args+2];
pid_t pid;
int estado;
const char* programa_arg= argv[1];

   int i;
   arguments[0] = programa_arg;
   arguments[n_args+1]= NULL;
   //printf("pROBANDO");
   for(i=0; i<n_args; i++){
      arguments[i+1]= argv[i+2];
   }

if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(-1);
}
else if(pid==0) {  //proceso hijo ejecutando el programa

	if( (execvp(programa_arg, arguments)<0)) {
		perror("\nError en el execl");
		exit(-1);
	}
}
wait(&estado);
printf("\nMi hijo %d ha finalizado con el estado %i\n",pid,estado>>8);

exit(0);

}
