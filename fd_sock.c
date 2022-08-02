#include <stdio.h>
#include <fcntl.h>
#include <bsd/sys/tree.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "fd_sock.h"
#include <string.h>
#include <stdlib.h>

//#define DEBUG

//#define verbose 1

#define NODE_DATA_SIZE 512

static struct FD_SOCK  head = RB_INITIALIZER (&head);


static int 
cmp (fd_sock_t *e1, fd_sock_t *e2)
{
    if (e1->fd == e2->fd){
       return 0;
    }else if (e1->fd > e2->fd){
       return 1;
    }else{
       return -1;
    }
}


RB_GENERATE (FD_SOCK, fd_sock, entry, cmp);



fd_sock_t*
get_fdsock_by_fd(fd_sock_map,fd)
    struct FD_SOCK* fd_sock_map;
    unsigned long long fd;
{
    fd_sock_t find;
    find.fd = fd;
    return RB_FIND(FD_SOCK,fd_sock_map,&find);
}

struct FD_SOCK*
create_fdsock_map (fd_sock_file)
     const char *fd_sock_file;
{

  FILE *fp = fopen (fd_sock_file, "r");


  if (!fp)
    {
      fprintf (stderr, "fd_sck file %s cannot open", fd_sock_file);
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
          fd_sock_t* pst=(fd_sock_t*)malloc(sizeof(fd_sock_t));
          memset (pst,'\0' ,sizeof (fd_sock_t));
          //999 socket:[289081082]
          sscanf(p_data,"%llu socket:[%llu]",&pst->fd,&pst->sockfd);
          #ifdef DEBUG
            fprintf(stderr,"parsed: %llu %llu\n",pst->fd,pst->sockfd);
          #endif
          fd_sock_t *exists_fd_sock;
          if((exists_fd_sock=RB_INSERT(FD_SOCK, &head, pst))!=NULL){
            fprintf(stderr,"[ERROR] insert rb_FD_SOCK, fd exists: %llu\n",exists_fd_sock->fd);
          
          }

      }
      }

  fclose (fp);
  return &head;
}
