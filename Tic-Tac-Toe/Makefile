CXX = g++
CXXFLAGS = -g -Wall
execs = ticTacToe

all: ticTacToe

ticTacToe: main.o Board.o Validation.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: Board.h Validation.h

#
# main.o: main.cpp Board.h Validation.h
# 	g++ -g -Wall -c main.cpp
#

Board.o: Board.cpp Board.h
	g++ -g -Wall -c Board.cpp

#
# Board.o: Board.h
#

Validation.o: Board.h Validation.h

run:
	./ticTacToe
	
clean:
	rm -f $(execs) *.o
