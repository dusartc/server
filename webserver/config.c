#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

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

char *root_directory(int argc, char **argv){
  if(argc > 2){
    printf("trop d'arguments\n%s [ROOT_DIR]\n", argv[0]);
    exit(EXIT_FAILURE);
  } if(argc == 2){
    char *dir = argv[1];
    struct stat dir_stat;
    stat(dir, &dir_stat);
    if(S_ISDIR(dir_stat.st_mode)){
      return dir;
    } else {
      printf("%s n'est pas un dossier\n", dir);
      exit(EXIT_FAILURE);
    }
  }
  return "/home/infoetu/dusartc/C/s4/server/public\0";
}
