#include <bsd/sys/tree.h>
#include "fd_sock.h"


int main(int argc,char *argv[]){

    struct FD_SOCK* sa=create_fdsock_map("sample/socket_file");

    printf("\nparse sample/sockfile result:\n");
    fd_sock_t* pst;
    RB_FOREACH(pst, FD_SOCK, sa){
        fprintf(stdout,"after inserted fd_sock: %llu %llu\n",pst->fd,pst->sockfd);
    }
    unsigned long long sample_fd=385;
    printf("\nget sockno by fd %llu\n",sample_fd);
    fd_sock_t *found=get_fdsock_by_fd(sa, sample_fd);
    if(found==NULL){
      printf("get fdsock by fd %llu failed\n",sample_fd);
    }else{
      printf("get sockfd: %llu\n",found->sockfd);
    }
    return 0;
}
