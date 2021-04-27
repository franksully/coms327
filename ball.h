#include <stdlib.h>

class PongBall {        
  public:          
    int x;  
    int y;  
    int speed; 
    int directionX;  
    int directionY;  
    PongBall(int x, int y, int z, int a, int q);   
    PongBall();   
    void ball_reverse_x();
		void ball_reverse_y();
		int ball_get_y();
		int ball_get_x();
		int ball_get_speed();
		void ball_bounce();
		void ball_move();
};

PongBall::PongBall(){   
	x = 40;
	y = 10;
	speed = 3;
	directionX = 4;
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
	if((this->ball_get_y() > 21) || (this->ball_get_y() < 0)){
		this->ball_reverse_y();
	}
	if(this->ball_get_x() < 4 || this->ball_get_x() > 74){
		this->ball_reverse_x();
	}
}

void PongBall::ball_move(){
	this->x += this->directionX;
	this->y += this->directionY;
}


