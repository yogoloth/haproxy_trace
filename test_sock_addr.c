#include <bsd/sys/tree.h>
#include "sock_addr.h"


int main(int argc,char *argv[]){

    struct sock_addr* sa=create_sockaddr_map("sample/proc_file");

    printf("\nresult:\n");
    sock_tcp_t* pst;
    RB_FOREACH(pst, sock_addr, sa){
        fd_ports* pports=&(pst->ports);
        //printf("after parsed: %x %x %x %x %llu\n",pports->ip1,pports->port1,pports->ip2,pports->port2,pst->sockfd);
        fprintf(stderr,"after inserted parsed to human: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,pst->sockfd);
    }
    return 0;
}
