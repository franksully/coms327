#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "paddle.h"
#include "ball.h"
#include "io.h"



int main(int argc, char *argv[])
{
	io_initialzie();
	refresh();
    PongBall *ball = new PongBall(); 
  
    
    for(int i = 0; i < 250; i++){

		Paddle *left = new Paddle(2,2,4,'w','s');
		Paddle *right = new Paddle(4,4,4,'u','j');
		left->draw();
		right->draw();
		refresh();
		}
    for(int i = 0; i < 150; i++){
			mvprintw(ball->ball_get_y(), ball->ball_get_x(), " ");
    	//mvprintw(44, ' ', "%d %d", ball_get_x(ball), ball_get_y(ball));
    	//mvprintw(ball_get_x(ball), ball_get_y(ball), "O");
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

