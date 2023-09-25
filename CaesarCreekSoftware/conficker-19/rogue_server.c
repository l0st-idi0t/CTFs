#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  int option = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if (server_socket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1234);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("Error binding socket");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) == -1) {
    perror("Error listening for connections");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Accept incoming connections
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
  if (client_socket == -1) {
    perror("Error accepting connection");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Client connected\n");

  // Main server logic goes here

  char buf[128];
  // S
  // Fflag.txt
  // PPrestidigitation
  // S
  char *line;

  line = "Fflag.txt\n";
  send(client_socket, line, 128, 0);
  printf("Sent: %s", line);

  line = "PPrestidigitation\n";
  send(client_socket, line, 128, 0);
  printf("Sent: %s", line);

  line = "S\n";
  send(client_socket, line, 128, 0);
  printf("Sent: %s", line);

  while(recv(client_socket, buf, 128, 0))
    printf("Received: %s\n", buf);

  close(client_socket);
  close(server_socket);

  return 0;
}

