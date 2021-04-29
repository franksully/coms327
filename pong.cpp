#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
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
  	
	Paddle *left = new Paddle(0,6,6,'w','s');
	Paddle *right = new Paddle(79,6,6,'u','j');
	refresh();
   
	char in;
	
	while (in != 'Q'){
		nodelay(stdscr,1);
		in = getch();
		left->moveUp(in);
		left->moveDown(in);
		right->moveUp(in);
		right->moveDown(in);
		left->draw();
		right->draw();
		mvprintw(ball->ball_get_y(), ball->ball_get_x(), " ");
		mvprintw(1, 0, line);
		mvprintw(22, 0, line);
		mvprintw(0, 2, "%d", scoreLeft);
		mvprintw(0, 77, "%d", scoreRight);

	   	ball->ball_move();

	   	ball->ball_bounce(left, right);
	   	if(ball->x < -2){
	   		scoreRight++;
	   		ball->ball_reset();
	   	}
	   	if(ball->x > 81){
	   		scoreLeft++;
	   		ball->ball_reset();
	   	}

	   	ball->ball_draw();
	  	nodelay(stdscr,1);
		if(getch() >= 0){
  			mvprintw(0, 5, "your num is %d", getch());
  		}

	 	refresh();
		usleep(64000);
	}    
	
    //mvprintw( 5,5, "O %d", ball_get_x(ball));


    refresh();
    //PongBall *ball = new PongBall(); 
    
    getchar();
	endwin();
    return 0;
}

