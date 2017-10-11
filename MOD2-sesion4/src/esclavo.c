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
#include <stdbool.h>
#include <math.h>

bool esPrimo(unsigned numero){
   double raiz=sqrt(numero);
   for(int i=2; i<=raiz; i++){
      //printf("esntrando %d\n", i);
      if(numero%i==0)
         return 0;
   }
   return 1;
}

int main(int argc, char *argv[]){
   if(argc<3){
      printf("El programa necesita dos parametros: extremo inferior y extremo superior.");
      exit(-1);
   }

   int num_bytes;
   int   ext_inf=atoi(argv[1]),
         ext_sup=atoi(argv[2]);

   for(unsigned i=ext_inf; i<=ext_sup; i++){
      if(esPrimo(i))
         printf("%d\n",i);
   }

   return 0;
}



