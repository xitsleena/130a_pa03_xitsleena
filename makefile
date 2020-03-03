bst: bst.o 
	g++ -std=c++11 -o bst.out bst.cpp 

bst.o: tree.h bst.cpp
	g++ -c bst.cpp

avl: avl.cpp 
	g++ -std=c++11 -o avl.out avl.cpp

avl.o: tree.h avl.cpp
	g++ -c avl.cpp