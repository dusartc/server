#include <signal.h>
#include <stdio.h>

void initialiser_signaux(void){
  if(signal(SIGPIPE, SIG_IGN) == SIG_ERR){
    perror("signal");
  }
}
