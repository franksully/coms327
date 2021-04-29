
class Paddle {
	public:
		int x, y, length;
		char upKey, downKey;
		
		void draw();
		void moveUp(char in);
		void moveDown(char in);
		void moveSmartRight(int x, int y, int directionX, int directionY);
		void moveSmartLeft(int x, int y, int directionX, int directionY);
		Paddle(int x, int y, int length, char up, char down);
};
