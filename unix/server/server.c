#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PROJECT_NAME "server"
#define SOCKET_PATH "./unix_socket"

int main(int argc, char **argv) {
    printf("This is project %s.\n", PROJECT_NAME);
    
    int connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("Fd %d \n", connection_socket);
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
	exit(EXIT_FAILURE);
	close(connection_socket);
    } 

    //int fd2 = connect(fd, 

    //while(1){}

    
    unlink(SOCKET_PATH);
    close(connection_socket);
    return 0;
}
