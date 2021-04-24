#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "io.h"

int kbhit(void) //stolen from stack overflow for how to get key without waiting 
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
	io_initialzie();
    mvprintw( 5, 5, "O");
    refresh();
    PongBall *ball = new PongBall(0,0,3); 
    getchar();
	endwin();
    return 0;
}

