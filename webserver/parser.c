#include "parser.h"
#include <string.h>
#include <stdio.h>

void parse(char *str){
  const char delim[3] = " ";
  char requete[2048];
  memset(requete, '\0', sizeof(requete));
  strcpy(requete, str);
  char *token;
  token = strtok(requete, delim);
  printf("parse :\n");
  while(token != NULL){
    printf("\t%s\n", token);
    token = strtok(NULL, delim);
  }
}
