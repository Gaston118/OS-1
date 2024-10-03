#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int shared_variable = 0;
  pid = fork();
  if (pid == 0) {
    shared_variable += 5;
    printf("Proceso hijo - Valor de la variable compartida: %d\n",
           shared_variable);

    exit(0);
  } else if (pid > 0) {
    wait(NULL);
    shared_variable -= 3;
    printf("Proceso padre - Valor de la variable compartida: %d\n",
           shared_variable);
  } else {
    printf("Ha ocurrido un error al crear el proceso hijo.\n");
  }
  return 0;
}