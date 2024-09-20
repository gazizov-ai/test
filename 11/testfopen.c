#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    FILE  *whitelist_file;;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int whitelist_size = 0;
    char* ip_to_str;

    whitelist_file = fopen("/home/almas/linux_c_projects/11/whitelist", "r");
    if (whitelist_file == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, whitelist_file)) != -1) {
        whitelist_size++;
    }
    struct sockaddr_in whitelist[whitelist_size];
    rewind(whitelist_file);
    for(int i=0; i < whitelist_size; i++)
    {
        if ((read = getline(&line, &len, whitelist_file)) == -1) break;
        //inet_pton(AF_INET, strndup(line, strlen(line)), &(whitelist[i].sin_addr));
        inet_aton(strndup(line, strlen(line)), &whitelist[i].sin_addr);
    }
    fclose(whitelist_file);
    for (int i=0; i<whitelist_size; i++)
    {
        //inet_ntop(AF_INET, &(whitelist[i].sin_addr), ip_to_str, INET_ADDRSTRLEN);
        printf("%s\n", inet_ntoa(whitelist[i].sin_addr));
    }
}