#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "paddle.h"
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
		mvprintw(ball->ball_get_y(), ball->ball_get_x(), " ");
		mvprintw(1, 0, line);
		mvprintw(22, 0, line);
		left->draw();
		right->draw();
   	ball->ball_move();
   	ball->ball_bounce();
   	ball->ball_draw();
    	
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

