#include "socket.h"
#include "parser.h"
#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

const char* mess = "Bonjour, nous vous remercions d'avoir choisi notre serveur.\nPour vous montrer notre gratitude voici une recette de cordon bleu.\n\nTout d'abord aller dans la grande surface la plus proche pour vous\nprocurer l'élément principal, votre paquet de cordons bleu surgelés.\n\nUne fois cette étape terminée, faites préchauffer votre four.\nFaites chauffer les cordons bleu, bravo vous avez reussi.\nVous pouvez donc dès maintenant déguster un mets fin et délicat.\n\nJe sais que cela nous vous suffit pas petite gourgandine, \nje vais donc vous expliquer comment faire du flan, tout d'abord allez chez le fermier, volez-lui une vache, vous récuperez le lait.\nMaintenant on fait bouillir le lait et on ajoute le sachet magique et vous mélangez.\n\nBravo vous savez préparer le président de la République !\n\n";

const char* error404 = "HTTP/1.1 400 Bad Request\r\nConnection: close\
                        \r\nContent-Length: 17\r\n\r\n400 Bad request";

char* ok = "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s";

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
      sleep(1);
      char buffer[BUFFER_SIZE];
      char *buf;
      while(1){
        memset(buffer, '\0', BUFFER_SIZE);
        int get=0, done=0;
        while((buf=fgets(buffer, BUFFER_SIZE, server))!=NULL){
          printf("%s", buffer);
          if(parse(buffer) == 1) get = 1;
          if(strcmp(buffer, "\r\n") == 0) done = 1;
          if(get == 1 && done == 1){
            fprintf(server, ok, strlen(mess),mess);
            fflush(server);
          } else if(done == 1){
            if(fwrite(error404, strlen(error404), 1, server) == 0){
              perror("fwrite");
              return EXIT_FAILURE;
            }
          }
        }
      }
    } else {
      close(socket_client);
    }
  }
  //close(socket_client); //deja fermée
  close(socket_serveur);
  return EXIT_SUCCESS;
}
