#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include "dirent.h"  //cabecera necesaria para el tratamiento de directorios
#include <string.h>

//MACROS PARA COMPROBAR PERMISOS DE EJECUCION DE GRUPO Y OTROS
#define PERM_XGRP(permiso) permiso & S_IXGRP == S_IXGRP
#define PERM_XOTH(permiso) permiso & S_IXOTH == S_IXOTH

//struct para guardar el numero de archivos regulares(con permisos x para grupo y otros) de un directorio y el tamaño de estos
struct FilesRegs{
   unsigned int n_files;
   unsigned int size_files;
};

/*
La funcion recorrer hace lo siguiente: entramos en el directorio que le pasamos y empieza a leer
sus archivos sin incluir . y .. Una vez que lee un archivo decide si este es regular o si es un directorio.
En caso de que sea regular, lo cuenta y pasa al siguiente pero en caso de que sea directorio se vuelve a llamar
a si misma con el path de dicho archivo.
*/

void recorrer(const char* path, struct FilesRegs* f_r){
   struct dirent* struct_dir;

   DIR* my_dir=opendir(path);
   if(my_dir==NULL){
      perror("\nError al abrir el directorio.\n");
      exit(-1);
   }

   while((struct_dir=readdir(my_dir)) != NULL){
      /*Este while recorre todo el directorio pasado, en el cual comprobara cada uno
      de sus archivos*/
      char current_file[1024];
      char name_current_file[256];
      sprintf(name_current_file, "%s", struct_dir->d_name);  //Nombre de cada archivo del directorio(solo nombre)
      sprintf(current_file, "%s/%s", path, struct_dir->d_name);  //Nombre de cada archivo del directorio(absoluto)

      struct stat atributos;     //Atributos de cada archivo del directorio
      //chdir(path);
      if(stat(current_file, &atributos) < 0){
         printf("Error al intentar acceder a los atributos de %s\n", current_file);
         perror("Error");
      }
      else{
         /*Comprueba si el archivo a analizar es directorio o no, en caso de que
          si lo sea se vuelve a llamar a la funcion, si no lo es se contabiliza.*/
         if(S_ISREG(atributos.st_mode)){
            if(PERM_XGRP(atributos.st_mode) && PERM_XOTH(atributos.st_mode)){
               printf("%s\t%lu\n", current_file, struct_dir->d_ino);
               f_r->n_files+=1;
               f_r->size_files+=atributos.st_size;
            }
         }
         else if(S_ISDIR(atributos.st_mode) && (strcmp(name_current_file, ".")!=0) && (strcmp(name_current_file, "..")!=0))
            recorrer(current_file, f_r);
      }
   }

   closedir(my_dir);
}

int main(int argc, char *argv[]){

if(argc<2){
   perror("\nError en la ejecucion del programa.\n Uso: ej2 <pathname>\n");
	exit(-1);
}

const char* path_name= argv[1];
struct FilesRegs reg_files={0,0};

//Recorremos con la funcion el directorio (y subdirectorios) del path pasado, guardando el valor de archivos regulares.
printf("Los i-nodos son: \n");
recorrer(path_name, &reg_files);

printf("\nEl path pasado es: %s y tiene %i archivos regulares con los permisos citados.\nEl tamaño total es: %i bytes.\n\n", path_name, reg_files.n_files, reg_files.size_files);

return 0;
}


