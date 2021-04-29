#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "ball.h"

#include "io.h"

PongBall::PongBall(){   
	x = 40;
	y = 10;
	speed = 3;
	directionX = 1;
	directionY = 1;
}


PongBall::PongBall(int xx, int yy, int z, int a, int q){    
	x = xx;
	y = yy;
	speed = z;
	directionX = a;
	directionY = q;
}

void PongBall::ball_reverse_x()
{
  this->directionX = -this->directionX;
}

void PongBall::ball_reverse_y()
{
  this->directionY = -this->directionY;
}

int PongBall::ball_get_y()
{
  return this->y;
}

int PongBall::ball_get_x()
{
  return this->x;
}

int PongBall::ball_get_speed()
{
  return this->speed;
}


void PongBall::ball_bounce(Paddle *left, Paddle *right){
	if((this->ball_get_y() > 21) || (this->ball_get_y() <= 2)){
		this->ball_reverse_y();
	}
	
	//mvprintw(0, 10, "loc %d", this->x % 79);
	
	Paddle *paddle; 
	int yes = 0;
	if(this->x < 1){
		//mvprintw(0, 10, "left");	
		paddle = left;
		yes = 1;
	}else if(this->x > 78){
		mvprintw(0, 10, "right");
		paddle = right;
		yes = 1;
	}
	if(yes){
		if(paddle->y <= this->y && paddle->y + paddle->length >= this->y){
			//mvprintw(0, 35, "I hit a paddle %d %d %d", this->y, paddle->y, paddle->y + paddle->length);
			this->ball_reverse_x();
		}
	}
}

void PongBall::ball_move(){
	this->x += this->directionX;
	this->y += this->directionY;
}

void PongBall::ball_draw(){
	mvprintw(this->y, this->x, "O");
}

void PongBall::ball_reset(){
	this->ball_reverse_x();
	this->x = 40;
	this->y = 10;
	this->ball_draw();
	mvprintw(0, 25, "press anything to contuine");	
	refresh();
	getchar();
	mvprintw(0, 25, "                          ");
	refresh();
}





