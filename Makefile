CXX = g++
RM = rm -f
ECHO = echo

CXXFLAGS = -Wall -Werror -ggdb3 -funroll-loops 


pong: pong.o io.o ball.o paddle.o
	$(CXX) $(CXXFLAGS) -o pong pong.o io.o ball.o paddle.o -lncurses
	
pong.o: pong.cpp io.h pong.h
	$(CXX) $(CXXFLAGS) -c pong.cpp -lncurses
	
io.o: io.h
	$(CXX) $(CXXFLAGS) -c io.cpp -lncurses

ball.o: pong.h io.h
	$(CXX) $(CXXFLAGS) -c ball.cpp -lncurses

paddle.o: paddle.h
	$(CXX) $(CXXFLAGS) -c paddle.cpp -lncurses

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o