#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void response(int);

void response(int sig_no) { printf("%s\n", strsignal(sig_no)); }

int main() {
  pid_t child;
  int status;
  child = fork();
  switch (child) {
  case -1:
    perror("fork");
  case 0:
    break;
  default:
    signal(SIGCHLD, response);
    wait(&status);
    break;
  }
}