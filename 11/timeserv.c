#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>

#define PORTNUM 5050
#define HOSTLEN 256
#define oops(msg) { perror(msg); exit(1); }

int main(int ac, char **av)
{
    struct sockaddr_in saddr, caddr;
    socklen_t addr_len = sizeof(caddr);
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id, sock_fd;
    FILE *sock_fp, *whitelist_file;
    char *ctime();
    time_t thetime;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int whitelist_size = 0, whitelisted = 0;
    whitelist_file = fopen("/home/almas/linux_c_projects/11/whitelist", "r");
    if (whitelist_file == NULL)
        oops("could not open whitelist");
    while ((read = getline(&line, &len, whitelist_file)) != -1) {
        whitelist_size++;
    }
    struct sockaddr_in whitelist[whitelist_size];
    rewind(whitelist_file);
    for(int i=0; i < whitelist_size; i++)
    {
        if ((read = getline(&line, &len, whitelist_file)) == -1) break;
        inet_aton(strndup(line, strlen(line)), &whitelist[i].sin_addr);
    }
    fclose(whitelist_file);

    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) oops("socket");
    if (setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");

    bzero((void *)&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);
    bcopy((void *)hp->h_addr_list[0], (void *)&saddr.sin_addr, hp->h_length);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;
    if (bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) oops("bind");

    if (listen(sock_id, 1) != 0) oops("listen");
    while(1)
    {
        sock_fd = accept(sock_id, (struct sockaddr *)&caddr, &addr_len);
        if (sock_fd == -1) oops("accept");
        sock_fp = fdopen(sock_fd, "w");
        if (sock_fp == NULL) oops("fdopen");
        char *ip_to_str = inet_ntoa(caddr.sin_addr);
        fprintf(sock_fp, "got a call from %s\n", ip_to_str);
        for (int i=0; i<whitelist_size; i++)
        {
            //fprintf(sock_fp, "%s\n", inet_ntoa(whitelist[i].sin_addr));
            if (memcmp(&caddr.sin_addr, &whitelist[i].sin_addr, sizeof(struct in_addr)) == 0)
            {
                whitelisted = 1;
                break;
            }
        }
        if (whitelisted == 1)
        {
            thetime = time(NULL);
            fprintf(sock_fp, "The time here is...");
            fprintf(sock_fp, "%s", ctime(&thetime));
        }
        else fprintf(sock_fp, "bad ip, connection rejected\n");
        fclose(sock_fp);
    }
}