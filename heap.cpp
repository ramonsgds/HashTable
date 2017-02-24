#include <iostream>
#include "heap.h"
#include <cmath>

using namespace std;


void MinHeap::printHeap(){
	for (vector<pair<string,int> >::iterator it = data.begin(); it != data.end(); ++it){
		cout << it->first << " " << it->second << endl;
	}
}


void MinHeap::swap(int lhs, int rhs){
	pair<string,int> temp = data[rhs];
	data[rhs] = data[lhs];
	data[lhs] = temp;
}

void MinHeap::trickleUp(int loc){
	int location = loc;
	int parent = (location -1)/d_ary;
	cout << "coord before: " << location << " " <<  parent << endl;
	printHeap();
	//ACCOUNT FOR BEGINNING OF TREE - NULL POINTER WILL SEG FAULT
	if (data.size() > 1){
		bool innerloopfinished = false;
		while(location >= 1 && data[location].second <= data[parent].second && innerloopfinished == false){
			cout << "coord while: " << location << " " <<  parent << endl;
			printHeap();
			if (data[location].second == data[parent].second){
				while (data[location].second == data[parent].second && innerloopfinished == false && location >= 1){
					if(data[location].first < data[parent].first){					
						myhashtable.update(pair<string,int>(data[parent].first,location));					
						myhashtable.update(pair<string,int>(data[location].first,parent));			
						swap(location,parent);
						location = parent;
						parent = (location-1)/d_ary;			
					}
					else{
						innerloopfinished = true;
					}
				}
			}
			else{
				myhashtable.update(pair<string,int>(data[parent].first,location));
				myhashtable.update(pair<string,int>(data[location].first,parent));
				swap(location,parent);
				location = parent;
				parent = (location-1)/d_ary;
				cout << "coord after: " << location << " " <<  parent << endl;
				printHeap();
			}
		}
	}
}

void MinHeap::heapify(int loc){
	 int location = loc;
	if (data.size() -1 <= abs(location*d_ary) ){
		return;
	}
	int smallerChild = d_ary*location + 1;
	for( int i = d_ary*location +1; i <= d_ary*location + d_ary -1; i++){
		if ( abs(i + 1) <= data.size() -1){	
			cout << "TEST: " << data[i].second << " " << data[i+1].second << endl;
			if ( data[smallerChild].second == data[i+1].second){ //CHECK SHOULD BE HERE FOR SEG FAULT
				if (data[i+1].first < data[smallerChild].first){
					smallerChild = i + 1;
				}
			}
			else if (data[i+1].second < data[smallerChild].second ){
				smallerChild = i +1;
			}
		}
	}
	cout << "HEAPIFY: " << location << " " << smallerChild << endl;
	if (data[location].second >= data[smallerChild].second){
		if ( data[location].second == data[smallerChild].second){
			if (data[location].first > data[smallerChild].first){
				myhashtable.update(pair<string,int>(data[location].first,smallerChild));
				myhashtable.update(pair<string,int>(data[smallerChild].first,location));
				swap(location,smallerChild);
				heapify(smallerChild);
			}
		}
		else{
			myhashtable.update(pair<string,int>(data[location].first,smallerChild));
			myhashtable.update(pair<string,int>(data[smallerChild].first,location));
			swap(location,smallerChild);
			heapify(smallerChild);
		}
	}
	

}


MinHeap::MinHeap(int d){
 	d_ary = d;
}


MinHeap::~MinHeap(){
  //Nothing for now
}

void MinHeap::add(string item, int priority){
	data.push_back(pair<string,int>(item,priority));
	myhashtable.add(pair<string,int>(item,data.size()-1));
	cout << "Added" << endl;
	trickleUp(data.size()-1);
    
}

const string & MinHeap::peek() const{
	if (data.size() == 0){
		throw out_of_range("Heap is empty!");
	}
	return data[0].first;
}

void MinHeap::remove(){
	if (isEmpty()){
		throw out_of_range("Heap is empty!");
	}
	cout << "deleting" << endl;
	if (data.size() == 1){
		cout <<"1" << endl;
		myhashtable.remove(data[0].first);
		data.pop_back();
	}
	else{
		pair<string,int> templast = data.back();
		myhashtable.remove(data[0].first);
		data[0] = templast;
		myhashtable.update(pair<string,int>(data[0].first,0));
		data.pop_back();
		heapify(0);
	}
	
}

void MinHeap::update(string item, int priority){
	int index = myhashtable.find(item);
	if ( data[index].second > priority){
		data[index].second = priority;
		int parent = (index-1)/d_ary;
		if (data[index].second <= data[parent].second){
			trickleUp(index);
		}
		else{
			heapify(index);
		}
	}
}

bool MinHeap::isEmpty(){
	return data.empty();
}

void MinHeap::deleteAll(){
	while(!isEmpty()){
		cout << peek() << " " << data[0].second << endl;
		remove();
	}
}