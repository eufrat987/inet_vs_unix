# inet_vs_unix

Test performance between inet socket and unix (local) socket.

## Test architecture

### Unix socket
Server <-- unix_socket (file) <-- data (size 1GB/100GB) -- Client

### Inet socket
Server <-- port 8080 <-- data (size 1GB/100GB) -- Client


## Test result (?)
### 1GB

Buffer size | 20 | 1024 | 10240 | 102400 
--- | --- | --- | --- | ---  
Unix socket | 1m2.384s | 0m1.336s | 0m0.266s | 0m0.200s
Inet socket | 0m33.589s | 0m1.076s | 0m0.445s | 0m0.322s

### 100GB
Buffer size  | 10240 | 102400 | 1024000 
--- | --- | --- | --- 
Unix socket | 0m27.426s | 0m19.908s | 0m16.029s
Inet socket | 0m37.817s | 0m31.756s | 0m25.813s

## Questions 
` man 7 unix `

> The AF_UNIX (also known as AF_LOCAL) socket family is used to communicate between processes on the
same machine efficiently.  Traditionally, UNIX domain sockets can be either unnamed, or bound to a
filesystem  pathname  (marked as being of type socket).  Linux also supports an abstract namespace
which is independent of the filesystem.

I expect that unix type server will receive data in less time than inet type server. 


## Other repo that tests this topic
[IPC Bench](https://github.com/rigtorp/ipc-bench.git)
