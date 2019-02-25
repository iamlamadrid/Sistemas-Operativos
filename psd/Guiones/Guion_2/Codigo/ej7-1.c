#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
 int N = 5;
 pid_t creado;
int i;
 for (i = 0; i < N; i++) {
   creado = fork();

   if(creado == 0){
     printf("Soy el hijo %d\n",i);

     break;
   }
   if(creado > 0){
     printf ("Soy el padre\n");
   }

   }

   switch (i) {
     case 0:
      printf("A soy el hijo %d\n",i);
      break;
      case 1:
       printf("B soy el hijo %d\n",i);
       break;
       case 2:
        printf("C soy el hijo %d\n",i);
        break;
        case 3:
         printf("D soy el hijo %d\n",i);
         break;
         case 4:
          printf("E soy el hijo %d\n",i);

   }
  }
