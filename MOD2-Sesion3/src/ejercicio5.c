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
   const int NPROCS= 5;
   pid_t childpid[NPROCS];
   pid_t p_wait;
   int i, hijos_vivos=NPROCS;
      /*
   Jerarquía de procesos tipo 1
   */
   for (i=0; i < NPROCS; i++) {
      if ((childpid[i]= fork()) == -1) {
         fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
         exit(-1);
      }

      else if(!childpid[i]){
         printf("\nSoy el hijo %d y mi padre es %d\n", getpid(), getppid());
         exit(0);
      }
   }

   for(i=0; i<NPROCS; i=i+2){
         if (waitpid(childpid[i],0,0) > 0){
            printf("\nTermino el proceso %d\t", childpid[i]);
            printf("Solo me quedan %d hijos.\n", --hijos_vivos);
         }
         else
            printf("\nError en wait.\n\n");
   }
   for(i=1; i<NPROCS; i=i+2){
         if (waitpid(childpid[i],0,0) > 0){
            printf("\nTermino el proceso %d\t", childpid[i]);
            printf("Solo me quedan %d hijos.\n", --hijos_vivos);
         }
         else
            printf("\nError en wait.\n\n");

   }

   return 0;
}
