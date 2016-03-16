#include <stdio.h>

void send_status(FILE *stream, int code, const char *reason_phrase);
void send_response(FILE *stream, int code, const char *reason_phrase, const char* message_body);
