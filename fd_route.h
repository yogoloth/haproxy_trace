#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "fd_sock.h"
#include "sock_addr.h"


//#define BUFSIZE 1024

typedef enum {
   from,
   to
} dirt;


fd_ports*
fd_to_ports(
    int fd,
    struct SOCK_ADDR* sa_map,
    struct FD_SOCK* fs_map);

char*
fds_to_route(
    unsigned int fd1,
    unsigned int fd2,
    struct FD_SOCK* fs_map,
    struct SOCK_ADDR* sa_map);
