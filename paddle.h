class Paddle {
	public:
		int x, y, length;
		char upKey, downKey;
		
		void draw();
		Paddle(int x, int y, int length, char up, char down);
};
