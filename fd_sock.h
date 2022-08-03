#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>



//#define NODE_DATA_SIZE 512

#ifndef __FD_SOCK_H
#define __FD_SOCK_H
typedef struct fd_sock
{
  RB_ENTRY (fd_sock) entry;
  unsigned long long fd;
  unsigned long long sockfd;
} fd_sock_t;

RB_HEAD (FD_SOCK, fd_sock)  ;

#endif

//int cmp (fd_sock_t *e1, fd_sock_t *e2);

RB_PROTOTYPE (FD_SOCK, fd_sock, entry, fd_sock_cmp);

struct FD_SOCK* create_fdsock_map (const char *fd_sock_file);

fd_sock_t* get_fdsock_by_fd( struct FD_SOCK* fd_sock_map, unsigned long long fd);


