#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PROJECT_NAME "client"
#define TO_SEND 1024LL * 1024 * 1024 // 1GB
#define BUFFER_SIZE 1024
#define LISTEN_PORT 8080

int main(int argc, char **argv) {
    printf("This is project %s.\n", PROJECT_NAME);

    int connection_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (connection_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(LISTEN_PORT);
    addr.sin_family = AF_INET;

    int ret = connect(connection_socket, (const struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        fprintf(stderr, "The server is down.\n");
        exit(EXIT_FAILURE);
    }

    long long int to_send = TO_SEND;
    char buffer[BUFFER_SIZE];
    memset(&buffer, 1, sizeof(buffer));
    while(to_send > 0) {
        size_t w = write(connection_socket, buffer, sizeof(buffer));
        if (w == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        to_send -= w;
    }

    printf("Sended %lld bytes\n", TO_SEND - to_send);

    return 0;
}
