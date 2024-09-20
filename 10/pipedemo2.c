#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define CHILD_MSG "i am a child process\n"
#define PAR_MSG "i am a parent process\n"
#define oops(m,x) {perror(m); exit(x);}

int main()
{
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;
    if(pipe(pipefd) == -1) oops("cannot get a pipe", 1);
    switch(fork())
    {
        case -1: oops("cannot fork", 2);
        case 0: 
        {
            len = strlen(CHILD_MSG);
            while(1)
            {
                if (write(pipefd[1], CHILD_MSG, len) != len) oops("write", 3);
                sleep(5);
            }
        }
        default:
        {
            len = strlen(PAR_MSG);
            while(1)
            {
                if (write(pipefd[1], PAR_MSG, len) != len) oops("write", 4);
                sleep(1);
                read_len = read(pipefd[0], buf, BUFSIZ);
                if (read_len <= 0) break;
                write(1, buf, read_len);
            }
        }
    }
    return 0;
}