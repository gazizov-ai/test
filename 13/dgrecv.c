#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "dgram.h"

#define oops(m, x) {perror(m); exit(x); }

int make_dgram_server_socket(int);
int get_internet_address(char *, int, int *, struct sockaddr_in *);
void say_who_called(struct sockaddr_in *);
int main(int ac, char **av)
{
    int port; int sock;
    char buf[BUFSIZ];
    size_t msglen;
    struct sockaddr_in saddr;
    socklen_t saddrlen;
    if (ac == 1 || (port = atoi(av[1])) <=0 )
    {
        fprintf(stderr, "usage: dgrecv portnumber\n");
        exit(1);
    }
    if ((sock = make_dgram_server_socket(port)) == -1) oops("cannot make socket", 2);
    saddrlen = sizeof(saddr);
    while((msglen = recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr *)&saddr, &saddrlen)) > 0)
    {
        buf[msglen] = '\0';
        printf("dgrecv: got a message: %s\n", buf);
        say_who_called((struct sockaddr_in *)&saddr);
    }
    printf("%d", msglen);
    return 0;
}

void say_who_called(struct sockaddr_in *addrp)
{
    char host[BUFSIZ];
    int port;
    get_internet_address(host, BUFSIZ, &port, addrp);
    printf(" from: %s:%d\n", host, port);
}