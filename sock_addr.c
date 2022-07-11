#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define verbose 1
#define NODE_DATA_SIZE 4096

typedef struct {
    struct in_addr ip1;
    int port1;
    struct in_addr ip2;
    int port2;
}fd_ports;

struct sock_tcp
{
    RB_ENTRY (sock_tcp) entry;
    long long sockfd;
    fd_ports ports;
};

int
cmp (struct sock_tcp *e1, struct sock_tcp *e2)
{
  return e1->sockfd > e2->sockfd;
}

RB_HEAD (sock_addr, sock_tcp) head = RB_INITIALIZER (&head);
RB_GENERATE (sock_addr, sock_tcp, entry, cmp);

struct sock_addr*
create_sockaddr_map(const char* proc_tcp_file){

    FILE *fp = fopen (proc_tcp_file, "r");


    if (!fp)
      {
        fprintf (stderr, "proc_tcp file %s cannot open", proc_tcp_file);
      }
    else
      {

        char n_data[NODE_DATA_SIZE];
        int n_count;
        while (fscanf (fp, "%s %d\n", (char *) &(n_data[0]), &n_count) !=
           EOF)
      {
        if (verbose)
          fprintf (stderr, "load %s %d\n", n_data, n_count);
        if(n_count>1)
        {
/*
            struct node *n = (struct node *) malloc (sizeof (struct node));
            memset (n,'\0' ,sizeof (struct node));
            strncpy (n->data, n_data, NODE_DATA_SIZE);
            n->count = n_count;
            RB_INSERT (rbtree, &head, n);
            if(! RB_INSERT(rbtree,&head,n))
            {
                fprintf(stderr,"load %s %d fail\n",n->data,n->count);
                exit(1);
            }
*/
        }
      }

      }
    fclose (fp);
    return &head;
}



