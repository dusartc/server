#include "parser.h"
#include <string.h>
#include <stdlib.h>

int parse(char *str, http_request *request){
  const char delim[3] = " ";
  char requete[2048];
  memset(requete, '\0', sizeof(requete));
  strcpy(requete, str);
  char *token = strtok(requete, delim);
  //printf("parse :\n");
  if(strcmp(token,"GET")==0){
    request->method = HTTP_GET;
  } else {
    request->method = HTTP_UNSUPPORTED;
    return 0;
  }
  token = strtok(NULL, delim);
  request->url = token;
  token = strtok(NULL, delim);
  request->major_version = (int)token[5];
  request->minor_version = (int)token[7];
  if(request->major_version == (int)'1' && 
      (request->minor_version == (int)'0' || request->minor_version == (int)'1')){
    return 1;
  }
  return 0;
}

char *fgest_or_exit(char *buffer, int size, FILE *stream){
  char *t = fgets(buffer, size, stream);
  if(t == NULL){
    exit(EXIT_SUCCESS);
  } 
  return t;
}
