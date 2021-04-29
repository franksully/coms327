#include <ncurses.h>

#include "paddle.h"

void Paddle::draw() {
	for (int i = 2; i < 22; i++) {
		mvprintw(i, this->x, " ");
	}
	for (int i = 0; i < length; i++) {
		mvprintw(this->y + i, this->x, "|");
	}
};
		
Paddle::Paddle(int x, int y, int length, char up, char down) {
	this->x = x;
	this->y = y;
	this->length = length;
	upKey = up;
	downKey = down;
};

void Paddle::moveUp(char in) {
	if (in == this->upKey) {
		this->y--;
	}
}

void Paddle::moveDown(char in) {
	if (in == this->downKey) {
		this->y++;
	}
}