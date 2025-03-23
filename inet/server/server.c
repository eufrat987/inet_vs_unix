#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PROJECT_NAME "server"
#define LISTEN_PORT 8080
#define LISTEN_BACKLOG 1
#define BUFFER_SIZE 1024
#define TO_RECEIVE 1024LL * 1024 * 1024 * 100 // 100GB

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

    int ret = bind(connection_socket, (struct sockaddr *) &addr, sizeof(addr));            
    if (ret == -1) {
        perror("bind");
    	close(connection_socket);
	exit(EXIT_FAILURE);
    }
    
    ret = listen(connection_socket, LISTEN_BACKLOG);
    if (ret == -1) {
        perror("listen");
    	close(connection_socket);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size;
    int client_fd = accept(connection_socket, (struct sockaddr *) &peer_addr, &peer_addr_size);
    if (client_fd == -1) {
        perror("accept");
    	close(connection_socket);
        exit(EXIT_FAILURE);
    }

    long long int to_receive = TO_RECEIVE;
    char buffer[BUFFER_SIZE];

    while (to_receive > 0) {
        ssize_t r = read(client_fd, buffer, sizeof(buffer));
        to_receive -= r;
    }

    printf("Received %lld bytes\n", TO_RECEIVE - to_receive);

    close(connection_socket);
    return 0;
}
