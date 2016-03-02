#include "parser.h"
#include <string.h>
#include <stdio.h>

int parse(char *str){
  const char delim[3] = " ";
  char requete[2048];
  memset(requete, '\0', sizeof(requete));
  strcpy(requete, str);
  char *token;
  token = strtok(requete, delim);
  printf("parse :\n");
  while(token != NULL){
    printf("\t%s\n", token);
    if(strcmp(token,"GET")==0){
      token = strtok(NULL, delim);
      if(strcmp(token,"/")==0){
        token = strtok(NULL, delim);
        if(strcmp(token, "HTTP/1.0\r\n") == 0 || strcmp(token, "HTTP/1.1\r\n") == 0){
          return 1;
        }
      } else {
        token = strtok(NULL, delim);
        if(strcmp(token, "HTTP/1.0\r\n") == 0 || strcmp(token, "HTTP/1.1\r\n") == 0){
          return 2;
        }
      }
    }
    token = strtok(NULL, delim);
  }
  return 0;
}
