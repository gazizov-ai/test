#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#define MSGLEN 512
#define oops(m,x) { perror(m); exit(x); }
#define SOCKNAME "tmp/logfilesock"

int main(int ac, char *av[])
{
    int sock;
    struct sockaddr_un addr;
    socklen_t addrlen;
    char msg[MSGLEN];
    int l;
    char sockname[] = SOCKNAME;
    time_t now;
    int msgnum = 0;
    char *timestr;
    addr.sun_family = AF_UNIX;
    strcpy(addr);
}