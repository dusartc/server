#include <stdio.h>

enum http_method {
  HTTP_GET,
  HTTP_UNSUPPORTED,
};

typedef struct {
  enum  http_method method;
  int   major_version;
  int   minor_version;
  char  *url;
} http_request;

int parse(char *str, http_request *request);
char *fgets_or_exit(char *buffer, int size, FILE *stream);
void skip_headers(FILE *stream);

char *rewrite_url(char *url);
