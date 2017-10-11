#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(argc != 3){
		printf("%dUso: ./ej5 SRC DEST\n\n", argc);
		return -1;
	}	
	int	fd_src, fd_dest;
	const char	*ptr_src;
	char *ptr_dest;
	struct stat s_src;
	
	fd_src = open(argv[1], O_RDONLY);
	if (fd_src == -1) {
		printf("Error al abrir archivo origen\n");
		return 1; 
	}
	
	if (fstat (fd_src, &s_src) == -1) {
		printf("Error al hacer stat\n");
		return 1; 
	}
	
	ptr_src = (char*) mmap(NULL, s_src.st_size, PROT_READ, MAP_SHARED, fd_src, 0);
	if (ptr_src == MAP_FAILED) {
		printf("Fallo el mapeo\n");
		return 1; 
	}	

	fd_dest = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0777);
	if (fd_dest == -1) {
		printf("Error al crear/abrir archivo destino\n");
		return 1; 
	}

	printf("Tamanio: %d\n", s_src.st_size);
	if(ftruncate(fd_dest, s_src.st_size)==-1) perror("Error en truncate");

	ptr_dest = (char*) mmap(NULL, s_src.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd_dest, 0);

	if (ptr_dest == MAP_FAILED) {
		printf("Fallo el mapeo\n");
		return 1; 
	}	

	memmove(ptr_dest, ptr_src, strlen(ptr_src));
	
	exit(0);
}
