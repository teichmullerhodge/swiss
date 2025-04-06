#include "response.h"
#include "../declarations/declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *http_response(u16 statusCode, const char *message,
                    const char *contentType) {
  char *response =
      (char *)malloc(strlen(message) + SAFE_SPACE); // 16 More spaces.

  if (response == NULL) {
    perror(OUT_OF_MEMORY);
    return NULL;
  }

  sprintf(response,
          "HTTP/1.1 %u\r\n"
          "Content-Type: %s\r\n"
          "Content-Length: %zu\r\n"
          "\r\n"
          "%s",
          statusCode, contentType, strlen(message), message);
  return response;
}
