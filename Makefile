CXX = g++
RM = rm -f
ECHO = echo

CXXFLAGS = -Wall -Werror -ggdb3 -funroll-loops


pong: pong.o io.o
	$(CXX) $(CXXFLAGS) -o pong pong.o io.o
	
pong.o: pong.cpp io.h
	$(CXX) $(CFLAGS) -c pong.cpp
	
io.o: io.h

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o