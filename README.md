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

Results from this repo: unix is ~7 times faster in throughput than inet.

&> time ./unix_thr 100 1000000 \
message size: 100 octets \
message count: 1000000 \
average throughput: 792317 msg/s \
average throughput: 633 Mb/s \
\
real	0m1.269s \
user	0m0.093s \
sys	0m1.140s \

&> time ./tcp_thr 100 1000000 \
message size: 100 octets \
message count: 1000000 \
average throughput: 146742 msg/s \
average throughput: 117 Mb/s \

real	0m7.822s \
user	0m0.233s \
sys	0m6.583s \

---
Observation from ipc-bench repo:

It is possible within scope of the same proceess create special unix socket.

       The socketpair() call creates an unnamed pair of connected sockets in the specified domain, of the
       specified  type,  and using the optionally specified protocol.  For further details of these argu‐
       ments, see socket(2).
