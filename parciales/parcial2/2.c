#include <signal.h>
#include <stdio.h>

void response(int);
void response(int sig_no) { printf("Linux\n"); }

int main() {
  
  while (1) {
    signal(SIGINT, response);
    printf("sleeping..\n");
    sleep(1);
  }
  return 0;
}

// Se imprime linux cada vez que se presiona ctrl+c. Pero no termina.