#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "ball.h"
#include "io.h"



int main(int argc, char *argv[])
{
	io_initialzie();

	refresh();
	
    refresh();
    PongBall *ball = new PongBall(); 
  
    
    for(int i = 0; i < 250; i++){


    	ball->ball_move();
    	ball->ball_bounce();
    	ball->ball_draw();
  		nodelay(stdscr,1);
  		//getch();
  		mvprintw(5, 5, "your num is %d", getch());
    	
    	refresh();
    	usleep(64000);
    }

    
    //mvprintw( 5,5, "O %d", ball_get_x(ball));
    refresh();
    mvprintw( 5, 5, "O");
    refresh();
    //PongBall *ball = new PongBall(); 
    
    
    getchar();
	endwin();
    return 0;
}

