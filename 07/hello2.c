#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#define LEFTEDGE 10
#define RIGHTEDGE 80
#define ROW 10
int main()
{
    char message[] = "Hello";
    char blank[] = "        ";
    int dir = +1;
    int pos = LEFTEDGE;
    initscr();
    clear();
    while(1)
    {
        move( ROW, pos);
        addstr(message);
        move(LINES-1, COLS-1);
        refresh();
        usleep(10000);
        move(ROW, pos);
        addstr(blank);
        pos += dir;
        if (pos >= RIGHTEDGE) dir = -1;
        if (pos <= LEFTEDGE) dir = +1;
    }
}