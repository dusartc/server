#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void traitement_signal(int sig){
  printf(" Signal %d reçu\n",sig);
  int status;
  waitpid(-1,&status,0);
}

void initialiser_signaux(void){
  if(signal(SIGPIPE, SIG_IGN) == SIG_ERR){
    perror("signal");
  }
  struct sigaction sa;
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART ;
  if (sigaction(SIGCHLD, &sa, NULL) == -1)  {
    perror("sigaction (SIGCHLD)");
  }
}

