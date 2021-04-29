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

void Paddle::moveSmartRight(int x, int y, int directionX, int directionY){
	if(directionX < 0){
		if(this->y + this->length/2 > y){
			this->y--;
		}else{
			this->y++;
		}
	}else{
		int counter = 0;
		while(x < this->x){
			x += directionX;
			counter++;
		} 
		
		int yPos = 1;
		for(;counter > 0; counter--){
			y += directionY * yPos;
			if(y <= 2 || y > 21){
				yPos = -yPos;
			}			
		}
		if(this->y + this->length/2 > y){
			this->y--;
		}else{
			this->y++;
		}

	}

}

void Paddle::moveDown(char in) {
	if (in == this->downKey) {
		this->y++;
	}
}
