/*
tarea8.c
Programa ilustrativo del uso de pipes y la redirecci�n de entrada y
salida est�ndar: "ls | sort", utilizando la llamada dup2.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]) {

  if(argc > 2){
    int fd[2];
    int fd1[2], nbytes;
    pid_t PID = getpid();
    int esclavos = 2;
    int ext_inf = atoi(argv[1]);
    int ext_sup = atoi(argv[2]);
    int diferencia = ext_sup - ext_inf;
    int n_hijo = -1;
    char buffer[80];
    char ext_inf_char[10], ext_sup_char[10], ext_dif_char[10], ext_dif1_char[10];

    pipe(fd); // Llamada al sistema para crear un pipe
    pipe(fd1);

    sprintf(ext_inf_char, "%d", ext_inf);             // Convertimos los argumentos a char para pasarselos a los hijos a traves de execlp
    sprintf(ext_sup_char, "%d", ext_sup);
    sprintf(ext_dif_char, "%d", diferencia);
    sprintf(ext_dif1_char, "%d", diferencia + 1);

    for(int i = 0; i < esclavos; i++){
      if(PID > 0){
        n_hijo = i;
        if ( (PID= fork())<0) {
          perror("\nError en fork");
          exit(-1);
        }
      }
      else
        break;
    }

    if (n_hijo == 0 && PID == 0) {          // Hijo 1
      close(fd[0]);
      dup2(fd[1],STDOUT_FILENO);
      execlp("./Ejercicio5_esclavo","./Ejercicio5_esclavo",ext_inf_char, ext_dif_char,NULL);
      printf("A\n");
      return 1;
    }
    else if(n_hijo == 1 && PID == 0){       // Hijo 2
      close(fd1[0]);
      dup2(fd1[1],STDOUT_FILENO);
      execlp("./Ejercicio5_esclavo","./Ejercicio5_esclavo",ext_dif1_char, ext_sup_char,NULL);
      return 1;
    }

    close(fd[1]);           // Cerramos ambos decriptores de escritura
    close(fd1[1]);

    dup2(fd[0],STDIN_FILENO);                             // Pasamos la entrada estandar a nuestro cauce sin nombre
    nbytes = read(fd[0],buffer,sizeof(buffer));           // Comenzamos a leer desde nuestro cuace y lo metemos en el buffer
    while(nbytes!=0){                                     // Escribimos en este bucle hasta que acabemos el cauce del hijo 1
      if(write(STDOUT_FILENO,buffer,strlen(buffer))==-1){
    		perror("Error en la escritura del hijo1.\n");
    		exit(EXIT_FAILURE);
    	}
    	memset(buffer,0,sizeof(buffer));
      nbytes = read(fd[0],buffer,sizeof(buffer));
    }

    dup2(fd1[0],STDIN_FILENO);
    nbytes = read(fd1[0],buffer,sizeof(buffer));
    while(nbytes!=0){
      if(write(STDOUT_FILENO,buffer,strlen(buffer))==-1){ // Escribimos en este bucle hasta que acabemos el cauce del hijo 2
        perror("Error en la escritura del hijo2.\n");
        exit(EXIT_FAILURE);
      }
      memset(buffer,0,sizeof(buffer));
      nbytes = read(fd1[0],buffer,sizeof(buffer));
    }
  }
  else{
    printf("Te faltan argumentos.\n");
  }
  return(0);
}
