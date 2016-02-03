#include "socket.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void){
  int socket_client, socket_serveur = creer_serveur(8080);
  while(1){
    socket_client = accept(socket_serveur, NULL, NULL);
    if(socket_client == -1){
      perror("socket client");
      exit(EXIT_FAILURE);
    }

    const char* mess = "bonjour\n";
    write(socket_client, mess, strlen(mess));
    sleep(1);

    char buffer[1024];
    while(1){
      memset(buffer, '\0', 1024);
      int n=0;
      if((n=read(socket_client, buffer, 1024))==-1){
        perror("read");
        return EXIT_FAILURE;
      }
      write(socket_client,buffer, strlen(buffer));
    }
  }
  close(socket_client);
  close(socket_serveur);
  return EXIT_SUCCESS;
}
