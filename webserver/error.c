#include "error.h"
#include <stdlib.h>

const char* erreur400 = "HTTP/1.1 400 Bad Request\r\nConnection: close\
                        \r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
 
const char* erreur404 = "HTTP/1.1 404 File Not Found\r\nContent-Length:\
                        18\r\n\r\n404 File not found\r\n";

void error400(FILE *stream){
  fprintf(stream, erreur400);
  fflush(stream);
  exit(EXIT_SUCCESS);
}

void error404(FILE *stream){
  fprintf(stream, erreur404);
  fflush(stream);
  exit(EXIT_SUCCESS);
}
