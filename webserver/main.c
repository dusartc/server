#include "socket.h"
#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main(void){
  int socket_client, socket_serveur = creer_serveur(8080);
  socket_client = accept(socket_serveur, NULL, NULL);
  if(socket_client == -1){
    perror("socket client");
    exit(EXIT_FAILURE);
  }
  initialiser_signaux();
  const char* mess = "Bonjour, nous vous remercions d'avoir choisi notre serveur.\nPour vous montrer notre gratitude voici un recette de cordon bleu.\n\nTout d'abord aller dans la grande surface la plus proche pour vous\nprocurer l'élément principal, votre paquet de cordons bleu surgelés.\n\nUne fois cette étape terminée, faites préchauffer votre four.\nfaites chauffer les cordons bleu, bravo vous avez reussi.\nVous pouvez donc dès maintenant déguster un met fin et délicat.\n\nJe sais que cela nous vous suffit pas gredin\nje vais donc vous expliquer comment faire du flan, tout d'abord allez chez le fermier volez-lui une vache\nvous récuperer le lait.\nMaintenant on fait bouillir le lait et on ajoute le sachet magique et vous mélangez.\n\nBravo vous savez préparer le président de la République !\n";
  sleep(1);
  write(socket_client, mess, strlen(mess));
  char buffer[BUFFER_SIZE];
  while(1){
    memset(buffer, '\0', BUFFER_SIZE);
    int n=0;
    if((n=read(socket_client, buffer, BUFFER_SIZE))==-1){
      perror("read");
      return EXIT_FAILURE;
    }
    write(socket_client,buffer, strlen(buffer));
  }
  close(socket_client);
  close(socket_serveur);
  return EXIT_SUCCESS;
}
