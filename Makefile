CXX = g++
CXXFLAGS = -Wall -Wno-uninitialized -std=c++11
BINARIES = bst avl

all: avl.out bst.out

avl.out: avl.cpp  
	$(CXX) $(CXXFLAGS) $^ -o avl
	
bst.out: bst.cpp 
	$(CXX) $(CXXFLAGS) $^ -o bst

clean:
	/bin/rm -f $(BINARIES) *.o
