#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "ball.h"

#include "io.h"

PongBall::PongBall(){   
	x = 1;
	y = 10;
	speed = 3;
	directionX = 3;
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


void PongBall::ball_bounce(){
	if((this->ball_get_y() > 21) || (this->ball_get_y() <= 2)){
		this->ball_reverse_y();
	}
	if(this->ball_get_x() <= 1 || this->ball_get_x() >= 78){
		this->ball_reverse_x();
	}
}

void PongBall::ball_move(){
	this->x += this->directionX;
	this->y += this->directionY;
}

void PongBall::ball_draw(){
	mvprintw(this->y, this->x, "O");
}


int PongBall::ball_collision(Paddle *left, Paddle *right){
	mvprintw(0, 10, "loc %d", this->x % 79);
	
	Paddle *paddle; 
	if(this->x < 1){
		mvprintw(0, 10, "left");	
		paddle = left;
	}else if(this->x > 78){
		mvprintw(0, 10, "right");
		paddle = right;
	}
	if(paddle){
		if(paddle->y <= this->y && paddle->y + paddle->length >= this->y){
			mvprintw(0, 35, "I hit a paddle");
			return 1;
		}
	}

	if((this->ball_get_y() > 21) || (this->ball_get_y() <= 2)){
		mvprintw(0, 35, "I hit a wall");
		return 1;
	}
	
	return 0;
}




