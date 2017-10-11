#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include "dirent.h"  //cabecera necesaria para el tratamiento de directorios
#include <string.h>
#include <ftw.h>

//MACROS PARA COMPROBAR PERMISOS DE EJECUCION DE GRUPO Y OTROS
#define PERM_XGRP(permiso) permiso & S_IXGRP == S_IXGRP
#define PERM_XOTH(permiso) permiso & S_IXOTH == S_IXOTH

//struct para guardar el numero de archivos regulares(con permisos x para grupo y otros) de un directorio y el tamaño de estos
struct FilesRegs{
   unsigned int n_files;
   unsigned int size_files;
};

int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) {
    if(S_ISREG(stat->st_mode)){
            if(PERM_XGRP(stat->st_mode) && PERM_XOTH(stat->st_mode)){
               printf ("Path: %s I-nodo: %o\n",path, stat->st_ino);
            }
         }

    return 0;
}


int main(int argc, char *argv[]){

if(argc<2){
   perror("\nError en la ejecucion del programa.\n Uso: ej2 <pathname>\n");
	exit(-1);
}

const char* path_name= argv[1];
struct FilesRegs reg_files={0,0};

//Recorremos con la funcion el directorio (y subdirectorios) del path pasado, guardando el valor de archivos regulares.
//printf("Los i-nodos son: \n");

if(nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
   perror("nftw");
}

//printf("\nEl path pasado es: %s y tiene %i archivos regulares con los permisos citados.\nEl tamaño total es: %i bytes.\n\n", path_name, reg_files.n_files, reg_files.size_files);

return 0;
}


