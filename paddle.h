class Paddle {
	public:
		int x, y, length;
		char upKey, downKey;
		
		void draw();
		void moveUp(char in);
		void moveDown(char in);
		Paddle(int x, int y, int length, char up, char down);
};