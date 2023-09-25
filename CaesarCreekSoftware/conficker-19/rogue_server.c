#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/aes.h>

void handle_client(int client_socket) {
    // Send the key immediately upon connection
    const char *key = "S send_flag.txt\n";
    send(client_socket, key, strlen(key), 0);

    char command[2];
    while (1) {
        // Receive and handle commands from the client
        if (recv(client_socket, command, sizeof(command), 0) <= 0) {
            // Error or client closed the connection
            break;
        }

        switch (command[0]) {
            case 'S':
                // Handle the "S" command
                // ...
                break;
            case 'F':
                // Handle the "F" command (if needed)
                // ...
                break;
            // Handle other commands as needed
        }
    }

    // Close the client socket when done
    close(client_socket);
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
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

    printf("Server listening on port 1234...\n");

    while (1) {
        struct sockaddr_in client_addr;
        int client_socket;
        socklen_t client_addr_len = sizeof(client_addr);

        // Accept incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Error accepting client connection");
            continue;
        }

        // Handle the client
        handle_client(client_socket);
    }

    // Close the server socket (never reached in this example)
    close(server_socket);

    return 0;
}

