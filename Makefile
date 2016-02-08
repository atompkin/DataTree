CXX = g++
CXXFLAGS = -ansi -Wall -ggdb3

all: mathtree

main.o: main.cpp mathtree.h asciitree.h parser.h scanner.h
	$(CXX) $(CXXFLAGS) -c main.cpp

asciitree.o: asciitree.cpp asciitree.h mathtree.h
	$(CXX) $(CXXFLAGS) -c asciitree.cpp

mathtree.o: mathtree.cpp mathtree.h
	$(CXX) $(CXXFLAGS) -c mathtree.cpp

scanner.o: scanner.c parser.h
	$(CXX) $(CXXFLAGS) -c scanner.c

parser.o: parser.cpp scanner.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

mathtree: main.o mathtree.o asciitree.o parser.o scanner.o
	$(CXX) $(CXXFLAGS) -o mathtree main.o mathtree.o asciitree.o parser.o scanner.o

scanner.h scanner.c: scanner.l
	flex -o scanner.c --header-file=scanner.h scanner.l

parser.h parser.cpp: parser.ypp
	bison -o parser.cpp --defines=parser.h parser.ypp

clean:
	rm -f *.o parser.h parser.cpp scanner.c scanner.h mathtree
