#include <stdlib.h>
#include "paddle.h"

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
		void ball_bounce(Paddle *left, Paddle *right);
		void ball_move();
		void ball_draw();
};
