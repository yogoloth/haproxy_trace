#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


typedef enum {
   from,
   to
} dirt;

typedef struct {
    struct in_addr ip1;
    int port1;
    struct in_addr ip2;
    int port2;
}fd_ports;

struct sock_tcp
{
    RB_ENTRY (sock_tcp) entry;
    long long sockfd;
    fd_ports ports;
};

struct fd_sock
{
    RB_ENTRY (fd_sock) entry;
    int fd;
    long long sockfd;
};

fd_ports*
fd_to_ports(pid,fd,proc_file,sock_file,d)
    pid_t pid;
    int fd;
    char* proc_file;
    char* sock_file;
    dirt d;
{
    return NULL;
}



int 
main(argc,argv)
    int argc;
    char *argv[];
{
    fd_ports* ports=fd_to_ports(3321,609,"sample/proc_file","sample/socket_file",from);
    //printf("%s\n",ports_str);
    return 0;
}
