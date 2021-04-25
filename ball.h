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
PongBall::PongBall();    
	x = 40;
	y = 10;
	speed = 3;
	directionX = 4;
	directionY = 1;
}

PongBall::PongBall(int xx, int yy, int z int a, int q);    
	x = xx;
	y = yy;
	speed = z;
	directionX = a;
	directionY = q;
}


