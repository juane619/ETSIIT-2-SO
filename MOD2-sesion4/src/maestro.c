/*
MAESTRO
Programa ilustrativo del uso de pipes y la redirección de entrada y
salida estándar: "ls | sort", utilizando la llamada dup2.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

const unsigned N_ESCLAVOS= 2;

int main(int argc, char *argv[]){
   if(argc<3){
      printf("El programa necesita dos parametros: extremo inferior y extremo superior.");
      exit(-1);
   }

   //Preparacion de argumentos de la llamada execlp()
   int   ext_inf1a=atoi(argv[1]),
         ext_sup1a=(atoi(argv[2])+atoi(argv[1]))/2,
         ext_inf2a= ext_sup1a+1,
         ext_sup2a=atoi(argv[2]);

   char  ext_inf1[10],
         ext_sup1[10],
         ext_inf2[10],
         ext_sup2[10];

   sprintf(ext_inf1, "%d", ext_inf1a);
   sprintf(ext_sup1, "%d", ext_sup1a);
   sprintf(ext_inf2, "%d", ext_inf2a);
   sprintf(ext_sup2, "%d", ext_sup2a);

   /////////////////////////////////////////////////

   //Cauces
   int fd1[2], fd2[2], fd;
   char buffer[25];
   memset(buffer,0,strlen(buffer));
   pid_t ret;
   int i;

   pipe(fd1); // pipe exclavo1
   pipe(fd2); // pipe exclavo2

   /////////////////////////////////////////////////

   //ESCLAVOS
   for(i=0; i<N_ESCLAVOS; i++){
      if ((ret= fork())<0) {
         perror("\Error en fork");
         exit(-1);
      }
      if(!ret){
         if(i==0){   //ESCLAVO1
            //Cerrar el descriptor de lectura de cauce en el proceso hijo
            close(fd1[0]);

            //dup2(): Duplicar el descriptor de escritura en cauce en el descriptor
            //correspondiente a la salida estda r (stdout), cerrado previamente en
            //la misma operación
            dup2(fd1[1], STDOUT_FILENO);	//Sustituimos salida estandar por el descriptor de escritura del esclavo1
            //close(fd1[1]);
            execlp("./esclavo","./esclavo",ext_inf1, ext_sup1,NULL); //ejecutamos programa esclavo
            perror("fallo en execlp");
            exit(EXIT_FAILURE);
         }
         if(i==1){   //ESCLAVO2
            //Cerrar el descriptor de lectura de cauce en el proceso hijo
            close(fd2[0]);
            dup2(fd2[1],STDOUT_FILENO);	//busca en la tabla de descriptores de archivos la primera que sea null y mete ahi lo que le pasamos(fd[1]) y esto tambien lo mete en la posicion de la tabla STDOUT_FILENO. Esto sirve para que a la vez que muestra por la salida estandar lo que tenga que mostrar, tambien se le pase al cauce(que es lo que hay en fd[1])
            //close(fd1[1]);
            execlp("./esclavo","./esclavo", ext_inf2, ext_sup2,NULL);
            perror("fallo en execlp");
            exit(EXIT_FAILURE);
         }
      }
   }

   //Cerramos descriptor de escritura en cauce del padre
   close(fd1[1]);
   close(fd2[1]);

   //LEEMOS DESDE EL CAUCE
   int rd1,rd2;
   memset(buffer,0,sizeof(buffer)); //borramos buffer por si contiene basura
   rd1=read(fd1[0],buffer,sizeof(buffer));

   while(rd1!=0){
      //char buffer[80];
      if(write(STDOUT_FILENO,buffer,strlen(buffer))==-1){
			perror("Error en la escritura del esclavo1.\n");
			exit(EXIT_FAILURE);
		}
		memset(buffer,0,strlen(buffer));//borramos buffer por si contiene basura
		rd1=read(fd1[0],buffer,sizeof(buffer));
   }

   rd2=read(fd2[0],buffer,sizeof(buffer));
   while(rd2!=0){
      //char buffer[80];
      if(write(STDOUT_FILENO,buffer,strlen(buffer))==-1){
			perror("Error en la escritura del esclavo2.\n");
			exit(EXIT_FAILURE);
		}
		memset(buffer,0,strlen(buffer));
		rd2=read(fd2[0],buffer,sizeof(buffer));
   }

   return 0;
}



