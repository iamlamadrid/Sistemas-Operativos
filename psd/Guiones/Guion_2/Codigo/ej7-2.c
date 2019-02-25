#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
 pid_t pid1;
   pid1 = fork();
if (pid1 > 0) {
    puts("Soy el abuelo\n");

}else{
  puts("Soy el padre\n");
  pid1 = fork();
}
if(pid1 == 0){
  puts("Soy el hijo\n");
}

  }
