#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "fd_route.h"


fd_ports*
fd_to_ports(fd,sa_map,fs_map)
    int fd;
    struct SOCK_ADDR* sa_map;
    struct FD_SOCK* fs_map;
{
    fd_sock_t *fs=get_fdsock_by_fd(fs_map, fd);
    if(fs==NULL)
        return NULL;
    sock_tcp_t *pst=get_socktcp_by_sock(sa_map,fs->sockfd);
    if(pst==NULL)
        return NULL;

    fd_ports* pports=&(pst->ports);
#ifdef DEBUG
    fprintf(stderr,"[DEBUG] get_socktcp_by_sock success: %s %u %s %u %llu\n",strdup(inet_ntoa(*(struct in_addr*)&pports->ip1)),pports->port1,strdup(inet_ntoa(*(struct in_addr*)&pports->ip2)),pports->port2,pst->sockfd);
#endif
    return pports;
}

char*
fds_to_route(fd1,fd2,fs_map,sa_map)
    unsigned int fd1;
    unsigned int fd2;
    struct FD_SOCK* fs_map;
    struct SOCK_ADDR* sa_map;
{
    static char buffer[BUFSIZE];
    memset(buffer,'\0',BUFSIZE);
    char tmp_buf[BUFSIZE]={0};
    fd_ports* pports=fd_to_ports(fd1,sa_map,fs_map);
    //fprintf(stdout,"%s:%u --> %s:%u --> ",strdup(inet_ntoa(*(struct in_addr*)&pports->ip2)),pports->port2,strdup(inet_ntoa(*(struct in_addr*)&pports->ip1)),pports->port1);
    sprintf(tmp_buf,"%s:%u --> ",inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2);
    strcat(buffer,tmp_buf);
    sprintf(tmp_buf,"%s:%u --> ",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1);
    strcat(buffer,tmp_buf);
    pports=fd_to_ports(fd2,sa_map,fs_map);
    //fprintf(stdout,"%s:%u --> %s:%u\n",strdup(inet_ntoa(*(struct in_addr*)&pports->ip1)),pports->port1,strdup(inet_ntoa(*(struct in_addr*)&pports->ip2)),pports->port2);
    sprintf(tmp_buf,"%s:%u --> ",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1);
    strcat(buffer,tmp_buf);
    sprintf(tmp_buf,"%s:%u",inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2);
    strcat(buffer,tmp_buf);
    return buffer;
}


