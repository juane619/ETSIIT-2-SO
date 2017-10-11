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

const unsigned N_ESCLAVOS= 2;

int main(int argc, char *argv[])
{
int fd[2];
pid_t esclavos[N_ESCLAVOS];

//pipe(fd); // Llamada al sistema para crear un pipe

for(int i=0; i<N_ESCLAVOS; i++){
	if ((esclavos[i]= fork())<0) {
		perror("\Error en fork");
		exit(-1);
	}
	if(!esclavos[i])
		break;
}

if(esclavos[0] == 0) { // esclavo1
printf("Soy el esclavo 1 y estoi aciendo cosas.");
	//Cerrar el descriptor de lectura de cauce en el proceso hijo
	//close(fd[0]);

	//Duplicar el descriptor de escritura en cauce en el descriptor
	//correspondiente a la salida estda r (stdout), cerrado previamente en
	//la misma operación
	//dup2(fd[1],STDOUT_FILENO);	//busca en la tabla de descriptores de archivos la primera que sea null y mete ahi lo que le pasamos(fd[1]) y esto tambien lo mete en la posicion de la tabla STDOUT_FILENO. Esto sirve para que a la vez que muestra por la salida estandar lo que tenga que mostrar, tambien se le pase al cauce(que es lo que hay en fd[1])
	//execlp("ls","ls",NULL);
	sleep(5);
	exit(0);
}
else if(esclavos[1] == 0){ // esclavo2
	printf("Soy el esclavo 2 y estoi aciendo cosas.");	
	exit(0);
	//Cerrar el descriptor de escritura en cauce situado en el proceso padre
	//close(fd[0]);

	//Duplicar el descriptor de lectura de cauce en el descriptor
	//correspondiente a la entrada estándar (stdin), cerrado previamente en
	//la misma operación
	//dup2(fd[1],STDOUT_FILENO);
	//execlp("sort","sort",NULL);
}
else{	//PADRE
	for(int j=0; j<N_ESCLAVOS; j++){
		if(wait())
			printf("Finaliza esclavo");
		else
			printf("error esclavo");
	}
exit(0);
	//Cerramos descriptor de escritura en cauce
	//close(fd[1]);
	//dup2(fd[0],STDIN_FILENO);
	//execlp("sort","sort",NULL);
}

return(0);
}



