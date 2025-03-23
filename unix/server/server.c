#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define PROJECT_NAME "server"
#define SOCKET_PATH "./unix_socket"
#define LISTEN_BACKLOG 1
#define BUFFER_SIZE 20
#define TO_RECEIVE 1000000

int connection_socket = -1;

void cleanup() {
    printf("Clean up\n");
    close(connection_socket);
    unlink(SOCKET_PATH);
}

void add_signals_handler() {
    if (signal(SIGINT, cleanup) == SIG_ERR) {
	perror("signal");
	exit(EXIT_FAILURE);
    } 
    if (signal(SIGTERM, cleanup) == SIG_ERR) {
	perror("signal");
	exit(EXIT_FAILURE);
    } 
}

int main(int argc, char **argv) {
    printf("This is project %s.\n", PROJECT_NAME);
    add_signals_handler();
    
    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connection_socket == -1) {
    	perror("socket");
	exit(EXIT_FAILURE);
    } 

    struct sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, SOCKET_PATH, sizeof(my_addr.sun_path));

    int ret = bind(connection_socket, (struct sockaddr *) &my_addr, sizeof(my_addr)); 
    if (ret == -1) {
    	perror("bind");
	cleanup();
	exit(EXIT_FAILURE);
    } 

    ret = listen(connection_socket, LISTEN_BACKLOG); 
    if (ret == -1) {
    	perror("listen");
	cleanup();
	exit(EXIT_FAILURE);
    }

    struct sockaddr_un peer_addr;
    socklen_t peer_addr_size;
    int client_fd = accept(connection_socket, (struct sockaddr *) &peer_addr, &peer_addr_size); 
    if (client_fd == -1) {
    	perror("accept");
	cleanup();
	exit(EXIT_FAILURE);
    }
   
    int to_receive = TO_RECEIVE;
    char buffer[BUFFER_SIZE];

    while (to_receive > 0) {
	ssize_t r = read(client_fd, buffer, sizeof(buffer)); 
	to_receive -= r;
    }


    cleanup();
    return 0;
}
