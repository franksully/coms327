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
};
<<<<<<< HEAD
PongBall::PongBall(){   
=======
PongBall::PongBall();    
>>>>>>> 1df157d... paddle?
	x = 40;
	y = 10;
	speed = 3;
	directionX = 4;
	directionY = 1;
}

<<<<<<< HEAD
PongBall::PongBall(int xx, int yy, int z, int a, int q){    
=======
PongBall::PongBall(int xx, int yy, int z int a, int q);    
>>>>>>> 1df157d... paddle?
	x = xx;
	y = yy;
	speed = z;
	directionX = a;
	directionY = q;
}

<<<<<<< HEAD
void ball_reverse_x(PongBall *b);
void ball_reverse_y(PongBall *b);
int ball_get_y(const PongBall *b);
int ball_get_x(const PongBall *b);
int ball_get_speed(const PongBall *b);
void ball_bounce(PongBall *b);
void ball_move(PongBall *b);
=======

>>>>>>> 1df157d... paddle?
