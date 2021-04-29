#include <ncurses.h>

#include "io.h"

void io_initialzie(void){
	WINDOW *w = initscr();
	cbreak();
	nodelay(w, TRUE);
	curs_set(0);
	keypad(w, TRUE);
	raw();
  	noecho();
	
}