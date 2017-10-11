//EJERCICIO2

#include <stdio.h>
#include <signal.h>

int contador[64]={0};   //64 Señales

static void handler (int signum){
	contador[signum]+=1;
    printf("\nLa senial %d se ha recibido %d veces.\n\n",signum,contador[signum]);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handler; // manejamos la señal con nuestra funcion
    sigemptyset(&sa.sa_mask);

    //Reiniciar las funciones que hayan sido interrumpidas por un manejador
    sa.sa_flags = SA_RESTART;

    printf("\nNo puedo capturar la senial 9");
    printf("\nNo puedo capturar la senial 19");
    printf("\nNo puedo capturar la senial 32");
    printf("\nNo puedo capturar la senial 33");

    for(int i=1;i<=64;i++)
        if(sigaction(i, &sa, NULL) == -1){
            printf("error en el manejador");
        }

    printf("ESperando el envio de señales..\n");

    while(1);
}
