#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define PROJECT_NAME "client"
#define SOCKET_PATH "../../server/build/unix_socket"
#define TO_SEND 1024LL * 1024 * 1024 * 100 // 100GB
#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    printf("This is project %s.\n", PROJECT_NAME);

    int connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connection_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path));

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
