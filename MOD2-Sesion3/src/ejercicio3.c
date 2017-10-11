//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int nprocs=5;
   pid_t childpid;
      /*
   Jerarquía de procesos tipo 1
   */
   for (int i=1; i < nprocs; i++) {
      if ((childpid= fork()) == -1) {
         fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
         exit(-1);
      }

      //Por cada vuelta del for se creara un hijo nuevo, guardando en childpid un 0
/*
      if(childpid) //El padre muere(termina su ejecucion) y el hijo crea a su vez otro hijo(sigue iterando), convirtiendose este en padre por lo que se crearan nprocs hijos de padres distintos.
         break;
*/

      if (!childpid) //El hijo muere(sale del for), por lo que el mismo padre crea siempre un hijo nuevo hasta nprocs veces.
         break;

   }
	printf("\npid= %d, ppid= %d\n", getpid(), getppid());


	exit(0);
}
