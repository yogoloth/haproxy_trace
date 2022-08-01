#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>



#define NODE_DATA_SIZE 512


typedef struct fd_sock
{
  RB_ENTRY (fd_sock) entry;
  unsigned long long fd;
  unsigned long long sockfd;
} fd_sock_t;

RB_HEAD (FD_SOCK, fd_sock) head ;

//int cmp (fd_sock_t *e1, fd_sock_t *e2);

RB_PROTOTYPE (FD_SOCK, fd_sock, entry, cmp);

struct FD_SOCK*
create_fdsock_map (const char *fd_sock_file);