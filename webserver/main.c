#include "socket.h"
#include "parser.h"
#include "config.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

const char* mess = "Bonjour, nous vous remercions d'avoir choisi notre serveur.\nPour vous montrer notre gratitude voici une recette de cordon bleu.\n\nTout d'abord aller dans la grande surface la plus proche pour vous\nprocurer l'élément principal, votre paquet de cordons bleu surgelés.\n\nUne fois cette étape terminée, faites préchauffer votre four.\nFaites chauffer les cordons bleu, bravo vous avez reussi.\nVous pouvez donc dès maintenant déguster un mets fin et délicat.\n\nJe sais que cela nous vous suffit pas petite gourgandine, \nje vais donc vous expliquer comment faire du flan, tout d'abord allez chez le fermier, volez-lui une vache, vous récuperez le lait.\nMaintenant on fait bouillir le lait et on ajoute le sachet magique et vous mélangez.\n\nBravo vous savez préparer le président de la République !\n\n";

int main(int argc, char **argv){
  char *dir = root_directory(argc, argv);
  printf("dossier utiliser : %s\n",dir);
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
        int parse_status, done=0, line_header=0;
        http_request request;
        memset(&request, '\0', sizeof(request));
        while((buf=fgets(buffer, BUFFER_SIZE, server))!=NULL){
          printf("%s", buffer);
          line_header++;
          if(line_header == 1) parse_status = parse(buffer, &request);
          if(strcmp(buffer, "\r\n") == 0) done = 1;
          if(parse_status == 0 && done == 1){
            send_response(server, 400, "Bad Request", "Bad Request\r\n");
          } else if(done == 1){
            if(request.method == HTTP_GET){
              printf("request.url dir (main): %s\n\t%s\n", request.url, dir);
              int file = 0;
              if((file = check_and_open(request.url, dir)) != -1){
                int size = get_file_size(file);
                char *rep = "Content-Length: ";
                sprintf(rep, "%d\r\n\r\n" ,size);
                send_response(server, 200, "OK", rep);
                copy(file, socket_client);
                fflush(server);
              } else {
                send_response(server, 404, "Not Found", "Not Found\r\n");
              } 
            } else {
              send_response(server, 400, "Bad Request", "Bad Request\r\n");
            }
            done = 0; line_header = 0; parse_status = 0;
          }
        }
        exit(EXIT_SUCCESS);
      }
    } else {
      close(socket_client);
    }
  }
  //close(socket_client); //deja fermée
  close(socket_serveur);
  return EXIT_SUCCESS;
}
