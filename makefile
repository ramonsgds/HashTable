all: doublet

doublet: heap.o hashtable.o
	g++ -g -Wall heap.o hashtable.o doublet.cpp -o doublet


heap.o:	heap.h heap.cpp
	g++ -c -Wall heap.cpp -o heap.o


hashtable.o: hashtable.h hashtable.cpp
		g++ -c -Wall hashtable.cpp -o hashtable.o