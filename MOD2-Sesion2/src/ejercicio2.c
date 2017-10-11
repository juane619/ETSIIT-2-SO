#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include "dirent.h"  //cabecera necesaria para el tratamiento de directorios

int main(int argc, char *argv[])
{

if(argc<3){
   perror("\nError en la ejecucion del programa.\n Uso: ej2 <pathname> <permisos_nuevos>\n");
	exit(-1);
}

struct stat atributos;
const char* path_name= argv[1];
struct dirent* struct_dir;

DIR* my_dir=opendir(path_name);
if(my_dir==NULL){
   perror("\nError al abrir el directorio.\n");
	exit(-1);
}

chdir(path_name); //Cambiamos el directorio de trabajo al directorio abierto para no tener problemas con stat

while((struct_dir=readdir(my_dir)) != NULL){
   char* current_file= struct_dir->d_name;   //Para leer cada archivo del directorio

   if(stat(current_file, &atributos) < 0)
      perror("Error al intentar acceder a los atributos.");
   else{
      if(!S_ISDIR(atributos.st_mode)){
         int perm_current_file= atributos.st_mode&0777;
         int permisos_nuevos= strtol(argv[2], NULL, 8)&0777;

         if(chmod(current_file, permisos_nuevos) < 0){
            printf("\nError en chmod para %s", current_file);
            printf("%s\t%i\t%o\n", current_file, errno, perm_current_file);
         }
         else
            printf("%s\t%o\t%o\n",current_file, perm_current_file, permisos_nuevos);
      }
   }
}

closedir(my_dir);
return 0;
}
