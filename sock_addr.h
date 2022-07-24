#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define NODE_DATA_SIZE 4096

typedef struct
{  
  //struct in_addr ip1;
  in_addr_t ip1;
  int port1;
  //struct in_addr ip2;
  in_addr_t ip2;
  int port2;
} fd_ports;

typedef struct sock_tcp
{
  RB_ENTRY (sock_tcp) entry;
  unsigned long long sockfd;
  fd_ports ports;
} sock_tcp_t;

RB_HEAD (sock_addr, sock_tcp) head ;

int cmp (sock_tcp_t *e1, sock_tcp_t *e2);

RB_PROTOTYPE (sock_addr, sock_tcp, entry, cmp);

struct sock_addr*
create_sockaddr_map (const char *proc_tcp_file);
