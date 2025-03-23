#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PROJECT_NAME "server"

void handle_error(int status, char* msg) {
    if (status == -1) {
    	perror(msg);
	exit(EXIT_FAILURE);
    }  
}

int main(int argc, char **argv) {
    printf("This is project %s.\n", PROJECT_NAME);
    
    int connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    handle_error(connection_socket, "socket");

    struct sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    int ret = bind(connection_socket, (struct sockaddr *) &my_addr, sizeof(my_addr)); 
    handle_error(ret, "bind");
    //int fd2 = connect(fd, 


    close(connection_socket);

    return 0;
}
