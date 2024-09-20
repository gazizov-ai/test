#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <arpa/inet.h>

#define SERVER_PORTNUM 2020
#define MSGLEN 128
#define TICKET_AVAIL 0
#define RECLAIM_INTERVAL 60
#define MAXUSERS 3
#define oops(x) { perror(x); exit(-1); }

int setup();
void free_all_tickets();
void shut_down();
void handle_request(char *req, struct sockaddr_in *client, socklen_t addlen);
char* do_hello(char *msg_p);
char* do_goodbye(char* msg_p);
static char* do_validate(char* msg_p);
void ticket_reclaim();
void narrate(char* msg1, char* msg2, struct sockaddr_in *clientp);