#include "sock_addr.h"
#include <bsd/sys/tree.h>


int main(int argc,char *argv[]){

    struct sock_addr* sa=create_sockaddr_map("sample/proc_file");
    //RB_FOREACH(x, name, head);
    return 0;
}
