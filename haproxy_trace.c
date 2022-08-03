#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "fd_route.h"


#define BUFSIZE 4096

int 
main(argc,argv)
    int argc;
    char *argv[];
{
    char* sess_file=argv[1];
    char* fd_sock_file=argv[2];
    char* sock_tcp_file=argv[3];
    //struct FD_SOCK* fs_map=create_fdsock_map("sample/socket_file");
    //struct SOCK_ADDR* sa_map=create_sockaddr_map("sample/proc_file");
    struct FD_SOCK* fs_map=create_fdsock_map(fd_sock_file);
    struct SOCK_ADDR* sa_map=create_sockaddr_map(sock_tcp_file);

    FILE *fp = fopen (sess_file, "r");
    if (!fp)
      {
        fprintf (stderr, "[ERROR] proc_tcp file %s cannot open", sess_file);
      }
    else
      {
        char buffer[BUFSIZE];
        char* p_data=&(buffer[0]);
        char dummy[255];
        while (fgets ((char *) p_data, BUFSIZE,fp) != NULL)
        {
            char src[1000];
            char fe[1000];
            char be[1000];
            unsigned int fd1;
            unsigned int fd2;
            
            sscanf(p_data,"%s %s %s %u %u",src,fe,be,&fd1,&fd2);
            char* res=fds_to_route(fd1,fd2,fs_map,sa_map);
            //printf("%s\n",res);
            printf("%s %s %s %s\n",src,fe,be,res);
        }
      }


    return 0;
}
