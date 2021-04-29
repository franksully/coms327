#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "ball.h"
#include "io.h"

const char *line = "________________________________________________________________________________";

int main(int argc, char *argv[])
{
	io_initialzie();
	
	mvprintw(1, 0, line);
	mvprintw(22, 0, line);
	
	refresh();
  PongBall *ball = new PongBall(); 
  unsigned int scoreLeft = 0;
  unsigned int scoreRight = 0;
	
	char mode;
	
	mvprintw(12, 30, "1 for 1-player mode");
	mvprintw(13, 30, "2 for 2-player mode");
	
	while (mode != 'Q' && mode != '1' && mode != '2'){
		mode = getch();
	}
	
	move(13,0);
	clrtoeol();
	move(12,0);
	clrtoeol();
  	
	Paddle *left = new Paddle(0,6,6,'w','s');
	Paddle *right;
	if (mode == '1') {
		right = new Paddle(79,6,1,'u','j');
	}
	else {
		right = new Paddle(79,6,6,'u','j');
	}
	mvprintw(0, 2, "%d", scoreLeft);
	mvprintw(0, 77, "%d", scoreRight);
	refresh();
	
	char in = mode;
	
	while (in != 'Q' && scoreLeft < 7 && scoreRight < 7){
		nodelay(stdscr,1);
		in = getch();
		mvprintw(1, 0, line);
		mvprintw(22, 0, line);
		left->moveUp(in);
		left->moveDown(in);
		if (mode == '1') {
			right->moveSmartRight(ball->x, ball->y, ball->directionX, ball->directionY);
		}
		else {
			right->moveUp(in);
			right->moveDown(in);
		}
		left->draw();
		right->draw();
		mvprintw(ball->ball_get_y(), ball->ball_get_x(), " ");

	   	ball->ball_move();

	   	ball->ball_bounce(left, right);
	   	if(ball->x < 0){
	   		scoreRight++;
				mvprintw(0, 2, "%d", scoreLeft);
				mvprintw(0, 77, "%d", scoreRight);
				if(scoreRight < 7) {
					ball->ball_reset();
				}
	   	}
	   	if(ball->x > 79){
	   		scoreLeft++;
				mvprintw(0, 2, "%d", scoreLeft);
				mvprintw(0, 77, "%d", scoreRight);
	   		if(scoreLeft < 7) {
					ball->ball_reset();
				}
	   	}

	   	ball->ball_draw();
	  	nodelay(stdscr,1);
	
	 	refresh();
		usleep(64000);
	}    
	
  mvprintw(12, 35, "GAME OVER!");


  refresh();
  //PongBall *ball = new PongBall(); 
    
  getchar();
	endwin();
  return 0;
}

