#include "heap.h"
#include <iostream>

using namespace std;


int main(){

	MinHeap myheap(4);

	myheap.add("Ramon",50);
	myheap.add("Ivete",200);
	myheap.add("Camila",40);
	myheap.add("Rogerio",70);

	myheap.add("Rachel",20);
	myheap.add("Tyler",400);
	myheap.add("Deborah",220);
	myheap.add("Carolina",5);

	myheap.add("Sarah",300);
	myheap.add("Elizabeth",30);
	myheap.add("Kate",100);
	myheap.add("Scarlett",80);

	myheap.add("Jennifer",60);
	myheap.add("Chris",90);
	myheap.add("Ethan",130);
	myheap.add("Tom",10000);

	myheap.add("Evan",1000);
	myheap.add("Noemi",400);
	myheap.add("Adam",250);
	myheap.add("Eva",270);

	myheap.add("Judith",1000000);
	myheap.add("Gabriel",700);
	myheap.add("John",800);
	myheap.add("Peter",330);

	myheap.add("Judas",900);
	myheap.add("Gaga",210);
	myheap.add("Zayn",340);
	myheap.add("Luana",260);

	myheap.add("Alex",390);
	myheap.add("Alexandra",410);
	myheap.add("Harley",1100);
	myheap.add("Roger",990);

	myheap.add("Lucas",960);
	myheap.add("Jesus",350);
	myheap.add("Cayla",380);
	myheap.add("Simon",450);

	myheap.add("Tony",1200);
	myheap.add("Elon",1800);
	myheap.add("Bill",2000);
	myheap.add("Steve",1050);

	myheap.printHeap();
	cout << endl;

	myheap.deleteAll();

	

	return 0;	
}