#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"


int main(int argc, char *argv[])
{
    initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();

    //WINDOW *win = newwin(10,10,1,1);

    //box(win, '*', '*');
    mvprintw( 5, 5, "O");
    //touchwin(win);
    //wrefresh(win);

    getchar();

    endwin();
    return 0;
}
