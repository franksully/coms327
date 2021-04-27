#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "pong.h"
#include "ball.h"
#include "ball.cpp"
#include "io.h"

int kbhit(void) //stolen from stack overflow for how to get key without waiting 
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
	io_initialzie();
    //mvprintw( 5, 5, "O");
    refresh();
    PongBall *ball = new PongBall(); 
    for(int i = 0; i < 150; i++){
    	//mvprintw(ball_get_x(ball), ball_get_y(ball), "O");
    	ball_move(ball);
    	ball_bounce(ball);
    	mvprintw(ball_get_y(ball), ball_get_x(ball), "O");
    	//mvprintw(44, 0, "%d %d", ball_get_x(ball), ball_get_y(ball));
    	refresh();
    	getchar();
    }

    
    //mvprintw( 5,5, "O %d", ball_get_x(ball));
    refresh();
    getchar();
	endwin();
    return 0;
}

