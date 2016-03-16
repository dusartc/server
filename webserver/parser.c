#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

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
  request->url = rewrite_url(token);
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

void skip_headers(FILE *stream){
  char buf[1024];
  while(fgest_or_exit(buf, sizeof(buf), stream) != NULL && strcmp(buf, "\n\r") != 0);
}

char *rewrite_url(char *url){
  char *index;
  if((index=strchr(url, '?')) != NULL){
    char *sub = malloc((int)(index - url) + 1);
    strncpy(sub, url, (int)(index - url));
    printf("\n%s\n",sub);
    sub[(int)(index - url)] = '\0';
    return sub; 
  }
  printf("url (rewrite_url): %s\n", url);
  return url;
}

int check_and_open(const char *url, const char *root){
  printf("url root (check_and_open): %s\n\t%s\n", url, root);
  printf("strlen(url), strlen(root): %zd, %zd\n", strlen(url), strlen(root));
  char path[1024];
  memset(path, '\0', 1024);
  /*
   *strcat(path, root);
   *strcat(path, url);
   */
  sprintf(path, "%s%s", root, url);
  printf("path (check_and_open): %s\n",path);
  struct stat p_stat;
  if(stat(path, &p_stat) == -1){
    perror("stat");
    return -1;
  }
  if(S_ISREG(p_stat.st_mode)){
    return open(path, O_RDONLY);
  }
  return -1;
}

int get_file_size(int fd){
  struct stat f_stat;
  fstat(fd, &f_stat);
  return f_stat.st_size;
}

int copy(int in, int out){
  char buf[2048];
  memset(buf, '\0', 2048);
  int n, total=0;
  while((n = read(in, buf, 2048)) != 0){
    total += n;
    write(out, buf, n);
  }
  return total;
}
