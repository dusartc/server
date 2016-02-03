#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int creer_serveur(int port){
  int socket_serveur;
  int optval = 1;
  socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_serveur == -1){
    perror("socket_serveur");
    fprintf(stderr,"erreur a la creation du socket");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  if(setsockopt(socket_serveur, SOL_SOCKET,SO_REUSEADDR, &optval,sizeof(int))==-1){
    perror("Can not see SO_REUSEADDR option");
    exit(EXIT_FAILURE);
  }

  if(bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1){
    perror("bind socket");
    fprintf(stderr, "erreur au bind du socket");
    exit(EXIT_FAILURE);
  }
  if(listen(socket_serveur, 10) == -1){
    perror("listen socket_serveur");
    exit(EXIT_FAILURE);
  }
  return socket_serveur;
}

  


