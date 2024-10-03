#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>

int main() {
  pid_t pid;
  int shared_variable = 0;
  pid = fork();
  if (pid == 0) {
    shared_variable += 5;
printf( "Valor de la variable compartida: %d\n", shared_variable);
  } else if (pid > 0) {
    shared_variable -= 3;
    printf("Valor de la variable compartida: %d\n", shared_variable);
  } else {
    printf("Ha ocurrido un error al crear el proceso hijo.\n");
  }
  return 0;
}