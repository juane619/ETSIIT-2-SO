/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	int f_write, f_read, n_bloque=0;
	char buffer[80], bq[13], bq2[30];

	char* output_file= "salida.txt";

	if(argc < 2)
		f_read= STDIN_FILENO;
	else{
		char* input_file= argv[1];

		if((f_read=open(input_file, O_RDONLY, S_IRUSR|S_IWUSR)) < 0){
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
		}
	}

	if( (f_write=open(output_file, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	//Leyendo 80 bytes desde input_file
	while(read(f_read, buffer, 80) > 0){
		sprintf(bq, "\nBloque %i: \n\n", n_bloque);
		write(f_write,bq,sizeof(bq));

		if(write(f_write,buffer,80) < 0) {
			perror("\nError en primer write");
			exit(EXIT_FAILURE);
		}

		n_bloque++;
	}

	//MODIFICACION ADICIONAL
	if(lseek(f_write,0,SEEK_SET)<0){
		perror("\nError al posicionar el puntero en la posicion 0.");
		exit(-1);
	 }

	sprintf(bq2, "El numero de bloques es: %i.\n\n", n_bloque-1);
	write(f_write, bq2, sizeof(bq2));

	//Cerramos archivos abiertos
   close(f_write);
   close(f_read);

	return EXIT_SUCCESS;
}
