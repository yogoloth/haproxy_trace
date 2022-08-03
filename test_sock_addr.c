#include <bsd/sys/tree.h>
#include <string.h>
#include "sock_addr.h"


int main(int argc,char *argv[]){

    struct SOCK_ADDR* sa=create_sockaddr_map("sample/proc_file");

    printf("\nparse sample/proc_file result:\n");
    sock_tcp_t* pst;
    RB_FOREACH(pst, SOCK_ADDR, sa){
        fd_ports* pports=&(pst->ports);
        //printf("after parsed: %x %x %x %x %llu\n",pports->ip1,pports->port1,pports->ip2,pports->port2,pst->sockfd);
        fprintf(stdout,"after inserted parsed to human: %s %u %s %u %llu\n",inet_ntoa(*(struct in_addr*)&pports->ip1),pports->port1,inet_ntoa(*(struct in_addr*)&pports->ip2),pports->port2,pst->sockfd);
    }

    printf("\nparse sample/socket_file result:\n");
    unsigned long long sample_sockno=302470345;
    sock_tcp_t* found=get_socktcp_by_sock(sa, sample_sockno);
    if(found==NULL){
        printf("get_socktcp_by_sock %llu error\n",sample_sockno);
    }else{
        pst=found;
        fd_ports* pports=&(pst->ports);
        fprintf(stdout,"get_socktcp_by_sock %llu success: %s %u %s %u %llu\n",sample_sockno,strdup(inet_ntoa(*(struct in_addr*)&(pports->ip1))),pports->port1,strdup(inet_ntoa(*(struct in_addr*)&(pports->ip2))),pports->port2,pst->sockfd);
    }

    return 0;
}
