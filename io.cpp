#include <ncurses.h>

#include "io.h"

void io_initialzie(void){

	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	resizeterm(1000, 1000);
	start_color();
}

void io_draw(void){

	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	start_color();
}
