#include "contents/response.h"
#include "declarations/declarations.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PORT 9000

void handle_client(int client_socket, clock_t timer) {
  char buffer[4096];
  int read_size = read(client_socket, buffer, sizeof(buffer) - 1);
  buffer[read_size] = '\0';

  if (strncmp(buffer, "GET /status ", 12) == 0) {

    clock_t current = clock();
    double uptime = (double)(current - timer) / CLOCKS_PER_SEC;
    const u16 RESPONSE_SIZE = 255;
    char *body = malloc(RESPONSE_SIZE);
    sprintf(body, "{\"Status\": true, \"Uptime\": %f}\n", uptime * 10000);
    char *response = http_response(OK, body, "application/json");
    write(client_socket, response, strlen(response));
    free(response);
    free(body);
  }

  if (strncmp(buffer, "GET /user ", 10) == 0) {

    const char body[] =
        "{\"Name\": \"Matheus\", \"Age\": 25, \"Favorite language\": \"C\"}\n";
    char *response = http_response(OK, body, "application/json");
    write(client_socket, response, strlen(response));
    free(response);

  } else {
    const char *response = "HTTP/1.1 404 Not Found\r\n"
                           "Content-Type: text/plain\r\n"
                           "Content-Length: 10\r\n"
                           "\r\n"
                           "Not Found\n";
    write(client_socket, response, strlen(response));
  }

  close(client_socket);
}

int main() {
  clock_t timer = clock();

  s32 server_fd, client_socket;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd == 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 10) < 0) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Servidor rodando em http://localhost:%d\n", PORT);

  while (1) {
    client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (client_socket < 0) {
      perror("Accept failed");
      continue;
    }
    handle_client(client_socket, timer);
  }

  return 0;
}