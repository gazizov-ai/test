#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "utmplib.c"
#define SHOWHOST

void show_time(time_t timeval)
{
    char st[30];
    strftime(st, sizeof st, "%F %R", (localtime(&timeval)));
    fputs(st, stdout);
}

void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-12.12s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_time);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}

int logout_tty(char *line)
{
    int fd;
    struct utmp rec;
    struct timeval tv;
    int len = sizeof(struct utmp);
    int retval = -1;
    if ((fd=open(UTMP_FILE, O_RDWR)) == -1) return -1;
    while(read(fd, &rec, len) == len )
    {
        printf("%s", rec.ut_line);
        if(strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0)
        {
            rec.ut_type = DEAD_PROCESS;
            if ((gettimeofday(&tv, NULL)) != -1)
            {
                rec.ut_tv.tv_sec = tv.tv_sec;
                if (lseek(fd, -len, SEEK_CUR) != -1)
                {
                    if (write(fd, &rec, len) == len)
                        retval = 0;
                }
                break;
            }
        }
    }
    if (close(fd) == -1) retval = -1;
    return retval;
}

int main()
{
    struct utmp *utbufp, *utmp_next();
    if (utmp_open(UTMP_FILE) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    while ((utbufp = utmp_next()) != ((struct utmp *) NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}

