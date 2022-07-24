#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sock_addr.h"
#include <string.h>

#define DEBUG

#define verbose 1





RB_HEAD (sock_addr, sock_tcp) head = RB_INITIALIZER (&head);

int
cmp (sock_tcp_t *e1, sock_tcp_t *e2)
{
    return e1->sockfd > e2->sockfd;
}

RB_GENERATE (sock_addr, sock_tcp, entry, cmp);

static char* substr(const char*str, unsigned start, unsigned end)
{
    unsigned n = end - start;
    static char stbuf[256];
    strncpy(stbuf, str + start, n);
    stbuf[n] = 0;
    return stbuf;
}

void *
create_sockaddr_map (proc_tcp_file)
     const char *proc_tcp_file;
{

  FILE *fp = fopen (proc_tcp_file, "r");


  if (!fp)
    {
      fprintf (stderr, "proc_tcp file %s cannot open", proc_tcp_file);
    }
  else
    {
      char buffer[NODE_DATA_SIZE];
      char* p_data=&(buffer[0]);
      char dummy[255];
      sock_tcp_t st;
      fd_ports* pports=&(st.ports);
      while (fgets ((char *) p_data, NODE_DATA_SIZE,fp) != NULL)
      {
          if (verbose)
              //fprintf (stderr, "load %s %d\n", n_data, n_count);
              fputs(p_data,stderr);
//1268: 5E10E00A:4A70 5077A80A:0CEA 01 00000000:00000000 00:00000000 00000000     0        0 296798886 1 ffff942f60e31f00 24 4 30 2 2
          sscanf(p_data,"%s %x:%x %x:%x %s %s %s %s %s %s %llu",dummy,&pports->ip1,&pports->port1,&pports->ip2,&pports->port2,dummy,dummy,dummy,dummy,dummy,dummy,&st.sockfd);
          if (verbose)
          {
            printf("parsed: %x %x %x %x %llu\n",pports->ip1,pports->port1,pports->ip2,pports->port2,st.sockfd);
            printf("parsed to human: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,st.sockfd);
          }
          RB_INSERT(sock_tcp, &head, &st);

      }

    }
  fclose (fp);
  return &head;
}
