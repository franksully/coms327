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
	left->draw();
	right->draw();
	refresh();
    
	for(int i = 0; i < 150; i++){
		mvprintw(ball->ball_get_y(), ball->ball_get_x(), " ");
		mvprintw(1, 0, line);
		mvprintw(22, 0, line);
   	ball->ball_move();
   	ball->ball_bounce();
   	ball->ball_draw();
  	nodelay(stdscr,1);
		if(getch() >= 0){
  		mvprintw(5, 5, "your num is %d", getch());
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

