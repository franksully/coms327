#include <stdlib.h>

class PongBall {        
  public:          
    int row;  
    int col;  
    int speed;   
    PongBall(int x, int y, int z);    
};

PongBall::PongBall(int x, int y, int z){
	row = x;
	col = y;
	speed = z;
}

