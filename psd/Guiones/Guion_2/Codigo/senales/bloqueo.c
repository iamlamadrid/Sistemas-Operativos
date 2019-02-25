#include <stdio.h>
#include <signal.h>

void f_manejadora(int);     /* funciones manejadoras */
main()
{
	sigset_t   nueva_mascara, vieja_mascara, pendiente;
	// preparo la mascara
	sigemptyset(&nueva_mascara);
	sigaddset(&nueva_mascara, SIGINT);
	// comunico la mascara al sistema mezclandolo por ejemplo
	if(sigprocmask(SIG_BLOCK,&nueva_mascara,&vieja_mascara)<0)
	      perror("Error al poner la mascara");
	puts("Puedes pulsar el control C 1 fase");
 	sleep(5);     // gastamos tiempo
	// miro si han hecho control C en los 5 segundos
	if (sigpending(&pendiente) < 0)
	      perror("error en pendiente");
	if (sigismember(&pendiente, SIGINT))
	      puts("tenemos un control C pendiente");
	// vuelvo a la situacion anterior
	puts("Voy a desbloquear senal");
        if (sigprocmask(SIG_SETMASK, &vieja_mascara, NULL) < 0)
              perror("Error al volver a la situacion original");
	puts("desbloqueada senal");
        puts("puedes pulsar el control C 2 fase");
	sleep(5);    // aquí si pulsamos control C terminara
        puts("Termine sin control C");
}

