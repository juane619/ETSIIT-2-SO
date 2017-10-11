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
   if(argc<2){
      printf("Debes especificar un parametro entero.");
      exit(-1);
   }

   pid_t pid;
   int arg_int= atoi(argv[1]);

   if((pid=fork())<0) {
      perror("\nError en el fork");
      exit(-1);
   }
   else if(pid==0) {  //proceso hijo ejecutando el programa
      arg_int%2==0?printf("El numero es par."):printf("El numero es impar.");
      printf("\n\n");
   }
   else{ //proceso padre ejecutando el programa
      arg_int%4==0?printf("El numero es divisible por 4."):printf("El numero no es divisible por 4.");
      printf("\n\n");
   }

   exit(0);

}
