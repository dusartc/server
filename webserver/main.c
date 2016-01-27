#include "socket.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void){
  int socket_client, socket_serveur = creer_serveur(8080);
  socket_client = accept(socket_serveur, NULL, NULL);
  if(socket_client == -1){
    perror("socket client");
    exit(EXIT_FAILURE);
  }

  const char* mess = "bonjour";
  write(socket_client, mess, strlen(mess));
  return 0;
}
