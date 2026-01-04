#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG_SIZE 12

int main() {
    int tcp_socket;
    int fd_client;
    int bytes_read;
    char buffer_1[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("socket");
        exit(1);
    }
    if (bind(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);

    }
    printf("Succesful bind.\n");
    if (listen(tcp_socket, BACKLOG_SIZE) < 0) {
        perror("listen");
        exit(1);
        
    }
    printf("Socket turned to passive state.\n");

    while (1) {
        fd_client = accept(tcp_socket, NULL, NULL);
        if (fd_client < 0) {
            perror("accept");
            continue;
        }
        printf("Connection Correctly established with client.\n"); 
        bytes_read = read(fd_client, buffer_1,BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer_1[bytes_read] = "\0";
            printf("%s", buffer_1);
        }


    }
}