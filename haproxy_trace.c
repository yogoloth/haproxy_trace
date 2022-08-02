#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "fd_sock.h"
#include "sock_addr.h"


typedef enum {
   from,
   to
} dirt;


fd_ports*
fd_to_ports(pid,fd,sa_map,fs_map,d)
    pid_t pid;
    int fd;
    struct SOCK_ADDR* sa_map;
    struct FD_SOCK* fs_map;
    dirt d;
{
    return NULL;
}



int 
main(argc,argv)
    int argc;
    char *argv[];
{
    struct SOCK_ADDR* sa_map=create_sockaddr_map("sample/proc_file");
    struct FD_SOCK* fs_map=create_fdsock_map("sample/socket_file");

    fd_ports* ports=fd_to_ports(3321,609,sa_map,fs_map,from);
    //printf("%s\n",ports_str);
    return 0;
}
