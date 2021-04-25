#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "io.h"

void ball_reverse_x(const PongBall *b)
{
  b->directionX = b->!directionX;
}

void ball_reverse_y(const PongBall *b)
{
  b->directionY = b->!directionY;
}

int ball_get_y(const PongBall *b)
{
  return b->y;
}

int ball_get_x(const PongBall *b)
{
  return b->x;
}

int ball_get_speed(const PongBall *b)
{
  return b->speed;
}

void bounce(const PongBall *b){
	if(ball_get_y(b) > 21) || ball_get_y(b) < 0){
		ball_reverse_y(b);
	}
	if(ball_get_x(b) < 3 || ball_get_x(b) > 77){
		ball_reverse_x(b);
	}
}


