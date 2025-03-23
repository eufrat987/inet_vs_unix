# inet_vs_unix

Test performance between inet socket and unix (local) socket.


## Test architecture

### Unix socket
Server <-- unix_socket (file) <-- data (size 1GB) -- Client

### Inet socket
Server <-- port 8080 <-- data (size 1GB) -- Client


## Test result (?)

### Unix socket
1m2.384s

### Inet socket
0m33.589s


## Questions 
` man 7 unix `

> The AF_UNIX (also known as AF_LOCAL) socket family is used to communicate between processes on the
same machine efficiently.  Traditionally, UNIX domain sockets can be either unnamed, or bound to a
filesystem  pathname  (marked as being of type socket).  Linux also supports an abstract namespace
which is independent of the filesystem.

I expected that unix type server will receive data in less time than inet type server. 
