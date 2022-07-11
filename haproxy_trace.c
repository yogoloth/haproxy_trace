#include <stdio.h>
#include <fcntl.h>


typedef enum {
   from,
   to
} dirt;

char*
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
    char* ports_str=fd_to_ports(3321,609,"sample/proc_file","sample/socket_file",from);
    printf("%s\n",ports_str);
    return 0;
}
