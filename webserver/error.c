#include "error.h"
#include <stdlib.h>
#include <string.h>

void send_status(FILE *stream, int code, const char *reason){
  fprintf(stream, "HTTP/1.1 %d %s\r\n", code, reason);
  if(code != 200){
    fprintf(stream, "Connection: close\r\n");
  }
}

void send_response(FILE *stream, int code, const char *reason, const char *body){
  send_status(stream, code, reason);
  fprintf(stream, "Content-Length: %zd\r\n\r\n%s", strlen(body), body);
  fflush(stream);
}
