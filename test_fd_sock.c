#include <bsd/sys/tree.h>
#include "fd_sock.h"


int main(int argc,char *argv[]){

    struct FD_SOCK* sa=create_fdsock_map("sample/socket_file");

    printf("\nresult:\n");
    fd_sock_t* pst;
    RB_FOREACH(pst, FD_SOCK, sa){
        fprintf(stderr,"after inserted fd_sock: %llu %llu\n",pst->fd,pst->sockfd);
    }
    return 0;
}
