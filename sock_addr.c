#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sock_addr.h"
#include <string.h>
#include <stdlib.h>

//#define DEBUG

//#define verbose 1


struct sock_addr  head = RB_INITIALIZER (&head);

RB_GENERATE (sock_addr, sock_tcp, entry, cmp);


int
cmp (sock_tcp_t *e1, sock_tcp_t *e2)
{
    if (e1->sockfd == e2->sockfd){
       return 0;
    }else if (e1->sockfd > e2->sockfd){
       return 1;
    }else{
       return -1;
    }
}



struct sock_addr*
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
      while (fgets ((char *) p_data, NODE_DATA_SIZE,fp) != NULL)
      {
          #ifdef DEBUG
              fputs(p_data,stderr);
          #endif
          sock_tcp_t* pst=(sock_tcp_t*)malloc(sizeof(sock_tcp_t));
          memset (pst,'\0' ,sizeof (sock_tcp_t));
          fd_ports* pports=&(pst->ports);
          //1268: 5E10E00A:4A70 5077A80A:0CEA 01 00000000:00000000 00:00000000 00000000     0        0 296798886 1 ffff942f60e31f00 24 4 30 2 2
          sscanf(p_data,"%s %x:%x %x:%x %s %s %s %s %s %s %llu",dummy,&pports->ip1,&pports->port1,&pports->ip2,&pports->port2,dummy,dummy,dummy,dummy,dummy,dummy,&pst->sockfd);
          #ifdef DEBUG
            fprintf(stderr,"parsed: %x %x %x %x %llu\n",pports->ip1,pports->port1,pports->ip2,pports->port2,pst->sockfd);
            fprintf(stderr,"parsed to human: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,pst->sockfd);
          #endif
          sock_tcp_t *exists_sock_tcp;
          if((exists_sock_tcp=RB_INSERT(sock_addr, &head, pst))!=NULL){
            fprintf(stderr,"[ERROR] insert rb_sock_addr, sockfd exists %llu\n",exists_sock_tcp->sockfd);
          
          }

          //printf("after insert:\n");
          //sock_tcp_t* pst_2;
          //RB_FOREACH(pst_2, sock_addr, &head){
          //    fd_ports* pports=&(pst_2->ports);
          //    printf("after rb_insert: %x %x %x %x %llu\n",pports->ip1,pports->port1,pports->ip2,pports->port2,pst_2->sockfd);
          //    printf("after rb_insert to human: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,pst_2->sockfd);
          //}
      }
      }

  fclose (fp);
  return &head;
}
