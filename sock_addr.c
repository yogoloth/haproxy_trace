#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sock_addr.h"
#include <string.h>


#define DEBUG

#define IP1 3
#define IP2 4
#define PID 10


RB_HEAD (sock_addr, sock_tcp) head = RB_INITIALIZER (&head);

int
cmp (struct sock_tcp *e1, struct sock_tcp *e2)
{
    return e1->sockfd > e2->sockfd;
}

RB_GENERATE (sock_addr, sock_tcp, entry, cmp);



struct sock_addr *
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
      while (fgets ((char *) p_data, NODE_DATA_SIZE,fp) != NULL)
      {
          if (verbose)
              //fprintf (stderr, "load %s %d\n", n_data, n_count);
              fputs(p_data,stderr);
          char *p=NULL;
          int i=0;
          while((p=strsep(&p_data," "))!=NULL)
          {
                      printf("a %s\n",p);
              switch(++i){
                  case IP1:
                      printf("%s\n",p);
                      break;
                  case IP2:
                      printf("%s\n",p);
                      break;
                  case PID:
                      printf("%s\n",p);
                      break;
              
              }

          }

      }

    }
  fclose (fp);
  return &head;
}
