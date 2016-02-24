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
  initialiser_signaux();
  while(1){
    socket_client = accept(socket_serveur, NULL, NULL);
    FILE *server = fdopen(socket_client, "w+");
    if(server == NULL){
      perror("fdopen");
      return EXIT_FAILURE;
    }
    if(fork()==0){
      if(socket_client == -1){
        perror("socket client");
        exit(EXIT_FAILURE);
      }
      const char* mess = "Bonjour, nous vous remercions d'avoir choisi notre serveur.\nPour vous montrer notre gratitude voici un recette de cordon bleu.\n\nTout d'abord aller dans la grande surface la plus proche pour vous\nprocurer l'élément principal, votre paquet de cordons bleu surgelés.\n\nUne fois cette étape terminée, faites préchauffer votre four.\nFaites chauffer les cordons bleu, bravo vous avez reussi.\nVous pouvez donc dès maintenant déguster un met fin et délicat.\n\nJe sais que cela nous vous suffit pas petite gourgandine, \nje vais donc vous expliquer comment faire du flan, tout d'abord allez chez le fermier volez-lui une vache, vous récuperez le lait.\nMaintenant on fait bouillir le lait et on ajoute le sachet magique et vous mélangez.\n\nBravo vous savez préparer le président de la République !\n\n";

      sleep(1);
      if(fwrite(mess, strlen(mess), 1, server) == 0){
        perror("fwrite");
        return EXIT_FAILURE;
      }
      char buffer[BUFFER_SIZE];
      char *buf;
      while(1){
        memset(buffer, '\0', BUFFER_SIZE);
        int n=0;
        while((buf=fgets(buffer, BUFFER_SIZE, server))!=NULL){
          fprintf(server, "<server> %s", buffer);
        }
        if(n==-1){
          perror("read");
          return EXIT_FAILURE;
        }
        if(n==0){
          close(socket_client);
          return EXIT_SUCCESS;
        }
      }
    } else {
      close(socket_client);
    }
  }
  //close(socket_client); //deja fermer
  close(socket_serveur);
  return EXIT_SUCCESS;
}
