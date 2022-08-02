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
fd_to_ports(fd,sa_map,fs_map,d)
    int fd;
    struct SOCK_ADDR* sa_map;
    struct FD_SOCK* fs_map;
    dirt d;
{
    fd_sock_t *fs=get_fdsock_by_fd(fs_map, fd);
    if(fs==NULL)
        return NULL;
    sock_tcp_t *pst=get_socktcp_by_sock(sa_map,fs->sockfd);
    if(pst==NULL)
        return NULL;

    fd_ports* pports=&(pst->ports);
    fprintf(stdout,"get_socktcp_by_sock success: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,pst->sockfd);
    return NULL;
}



int 
main(argc,argv)
    int argc;
    char *argv[];
{
    struct SOCK_ADDR* sa_map=create_sockaddr_map("sample/proc_file");
    struct FD_SOCK* fs_map=create_fdsock_map("sample/socket_file");

    fd_ports* ports=fd_to_ports(609,sa_map,fs_map,from);
    //printf("%s\n",ports_str);

    return 0;
}
