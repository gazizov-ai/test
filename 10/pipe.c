#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define oops(m, x) {perror(m); exit(x);}

int main(int ac, char *av[])
{
    int thepipe[2], newfd, pid;
    if (ac != 3)
    {
        fprintf(stderr, "usage: pipe cmd1 cmd2\n");
        exit(1);
    }
    if (pipe(thepipe) == -1) oops("cannot get a pipe", 1);
    if ((pid = fork()) == -1) oops("cannot fork", 2);
    if (pid > 0)
    {
        close(thepipe[1]);
        if (dup2(thepipe[0], 0) == -1) oops("cannot redirect stdin", 3);
        close(thepipe[0]);
        execlp(av[2], av[2], NULL);
        oops(av[2], 4);
    }
    close(thepipe[0]);
    if (dup2(thepipe[1], 1) == -1) oops("cannot redirect stdout", 4);
    close(thepipe[1]);
    execlp(av[1], av[1], NULL);
    oops(av[1], 5);
}