// EJERCICIO3

#include <stdio.h>
#include <signal.h>

int main()

{
sigset_t new_mask;

/* inicializar la nueva mascara de señales, añadiendo todas*/
sigfillset(&new_mask);

/*Borramos la señal SIGUSR1 al conjunto de señales new_mask*/
sigdelset(&new_mask, SIGUSR1);

/*VARIANTE DEL PROGRAMA 1
//Bloquear a cualquier señal excepto SIGUSR1//
sigprocmask(SIG_BLOCK, &new_mask, 0);

while(1){}
*/

/*VARIANTE DEL PROGRAMA 2

//esperar a cualquier señal excepto SIGUSR1
sigsuspend(&new_mask);

*/

}
