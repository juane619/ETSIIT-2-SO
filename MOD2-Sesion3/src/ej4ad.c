/*Ejercicio 4. Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se
identificará en la salida estándar, mostrando un mensaje del tipo Soy el hijo PID. El proceso
padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez que detecte
la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:
Acaba de finalizar mi hijo con <PID>
Sólo me quedan <NUM_HIJOS> hijos vivos
*/

#include<sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){           // Cuidado con el buffer del printf al crear hijos, puede crear confusión y que los hjos impriman aunque no deban hacerlo
  int nprocs = 4;
  int status;
  pid_t childpid = 1, ch2;

  for (int i = nprocs; i >= 0; i--) {      // Creamos los cuatro procesos hijos restantes
    if(childpid)
      if ((childpid= fork()) == -1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
        exit(-1);
      }
    if(!childpid){
      printf("\nSoy el hijo %d\n", getpid());
      exit(0);
    }
    if(ch2=wait()){
		printf("Ch2: %d\n", ch2);
      printf("Acaba de finalizar mi hijo con %d\n", childpid);
      printf("Sólo me quedan %d hijos vivos.\n", i);
    }
  }
sleep(5);
exit(0);
}
