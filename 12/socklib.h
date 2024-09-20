#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>

#define HOSTLEN 256
#define BACKLOG 1

int make_server_socket(int portnum);
int make_server_socket_q(int portnum, int backlog);
int connect_to_server(char* host, int portnum);