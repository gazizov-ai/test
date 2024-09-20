#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "dgram.h"

static int pid = -1;
static int sd = -1;
static struct sockaddr serv_addr;
static socklen_t serv_alen;
static char ticket_buf[128];
static int have_ticket = 0;

#define MSGLEN 128
#define SERVER_PORTNUM 2020
#define HOSTLEN 512
#define oops(p) { perror(p); exit(1); }

void setup();
void shut_down();
int get_ticket();
int release_ticket();
char *do_transaction(char* msg);
void narrate(char *msg1, char* msg2);
void syserr(char* msg1);