#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <error.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>

#define BUFFER_SIZE 4096

int set_nonblocking(int fd)
{
    int flags;
    if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int
main(argc,argv)
    int argc;
    char *argv[];
{
    char *socket_file=argv[1];
    struct sockaddr_un addr;
    //char *SOCKET_NAME="/var/lib/haproxy/stats";
    char *SOCKET_NAME=socket_file;
    char *cmd="show sess\n";
    char buffer[BUFFER_SIZE];
    int ret;
    fd_set rfds;
	FD_ZERO(&rfds);

	int fd=socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd<0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

/*
        ret=set_nonblocking(fd);
	if(fd<0){
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
*/

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
	ret = connect (fd, (const struct sockaddr *) &addr,
			sizeof(struct sockaddr_un));
	if (ret == -1) {
		fprintf(stderr, "The server is down.\n");
		exit(EXIT_FAILURE);
	}

        ret = write(fd, cmd, strlen(cmd) + 1);
	if (ret == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
        for(;;){
/*
		FD_SET(fd, &rfds);
                int retval = select(fd+1,&rfds,NULL,NULL,NULL);
                if  (retval<0)
                {
                    perror("select error");
		    exit(EXIT_FAILURE);
                }

                if(FD_ISSET(fd, &rfds))
		{
*/
			//memset(&buffer[0], 0, BUFFER_SIZE);
			ret = read(fd, buffer, BUFFER_SIZE);
			if (ret == -1) {
				perror("read");
				if(errno==EAGAIN)
					continue;
				else
					exit(EXIT_FAILURE);
			}
			//else if (ret == 0||ret < BUFFER_SIZE)
			else if (ret == 0)
				break;
			//if (buffer[ret - 1] == 0){
			//   break;
			//}
			//fprintf(stdout,"last_char %x size %d\n",buffer[ret-1],ret);

			buffer[ret - 1] = 0;
			printf("%s",buffer);
			shutdown(fd, SHUT_WR);
//		}
        }

	putchar('\n');

	close(fd);

	exit(EXIT_SUCCESS);
	return 0;

}
