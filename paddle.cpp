#include <ncurses.h>

#include "paddle.h"

Paddle::draw() {
	for (int i = 2; i < 22; i++) {
		mvprintw(i, this->x, (const char*) ' ');
	}
	for (int i = 0; i < length; i++) {
		mvprintw(this->y + i, this->x, (const char*) '|');
	}
};
		
Paddle::Paddle(int x, int y, int length, char up, char down) {
	this->x = x;
	this->y = y;
	this->length = length;
	upKey = up;
	downKey = down;
};