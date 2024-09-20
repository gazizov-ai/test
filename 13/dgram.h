#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>


int make_internet_address();
int make_dgram_server_socket(int portnum);
int make_dgram_client_socket();
int get_internet_address(char *host, int len, int *portp, struct sockaddr_in *addrp);