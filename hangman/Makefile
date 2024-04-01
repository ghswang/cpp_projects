CXX = g++
CXXFLAGS = -Wall
exec = hangman

all: $(exec)

$(exec): main.o Word.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: Word.h

Word.o: Word.h

run:
	./$(exec)

clean:
	rm -f $(exec) *.o