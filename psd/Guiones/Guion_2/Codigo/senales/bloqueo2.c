#include <stdio.h>
#include <signal.h>

main()
{
   int creado, ppid;
   void f_manejadora();          /* funciones manejadoras */
   sigset_t     nueva_mascara, vieja_mascara, pendiente;


   if (signal(SIGINT, f_manejadora) == SIG_ERR)
      perror("Error al senalar el control c");

   sigemptyset(&nueva_mascara);
   sigaddset(&nueva_mascara, SIGINT);

   if (sigprocmask(SIG_BLOCK, &nueva_mascara, &vieja_mascara) < 0)
      perror("Error al poner la mascara");

   sleep(5);     // gastamos tiempo

   if (sigpending(&pendiente) < 0)
      perror("error en pendiente");
   if (sigismember(&pendiente, SIGINT))
      puts("tenemos un control C pendiente");

    // volvemos a la situacion anterior
   if (sigprocmask(SIG_SETMASK, &vieja_mascara, NULL) < 0)
      perror("Error al volver a la situacion original");
   puts("desbloqueada senal");

   sleep(5);    // aqui si pulsamos control C terminara

}


void f_manejadora()
{
   puts("llego la senal");
   if (signal(SIGINT, SIG_DFL) == SIG_ERR)
      perror("Error al volver por defecto");
}
