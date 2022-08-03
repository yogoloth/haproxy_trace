#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "fd_route.h"





int 
main(argc,argv)
    int argc;
    char *argv[];
{
    struct FD_SOCK* fs_map=create_fdsock_map("sample/socket_file");
    struct SOCK_ADDR* sa_map=create_sockaddr_map("sample/proc_file");

    int fd1=385;
    int fd2=407;
    char* res=fds_to_route(fd1,fd2,fs_map,sa_map);
    printf("%s\n",res);

    return 0;
}
