#include <iostream>
#include "hashtable.h"
#include <cmath>


using namespace std;

HashTable::HashTable(){
	data = new vector<pair<string,int> >*[31];
	for ( int i =0; i < 31; i++){
		data[i] = new vector<pair<string,int> >;
	}
	size = 31;
	alpha = 0;
}

HashTable::~HashTable(){
	for ( int i = 0; i < size; i++){
		delete data[i];
	}
	delete[] data;
}

void HashTable::add(pair<string,int> new_item){

	if (1.0*(alpha*size+1)/size > 1){
		 resize();
		 cout << "Heeey, I just resized :3 " << endl;
	}

	long long index = hash_str(new_item.first);
	for(vector<pair<string,int> >::iterator it = data[index]->begin(); it != data[index]->end(); ++it){
		if (it->first == new_item.first){
			throw invalid_argument("Key already exists in the Hash Table!");
		}
	}
	data[index]->push_back(new_item);
	alpha = 1.0*(alpha*size+1)/size;
}


const int& HashTable::find(string key) const{
	long long index = hash_str(key);
	for(vector<pair<string,int> >::iterator it = data[index]->begin(); it != data[index]->end(); ++it){
		if (it->first == key ){
			return it->second;
		}
	}
	throw out_of_range("Not found!");
}

void HashTable::remove (string key){
	long long index = hash_str(key);
	for(vector<pair<string,int> >::iterator it = data[index]->begin(); it != data[index]->end(); ++it){
		if (it->first == key ){
			data[index]->erase(it);
			alpha = 1.0*(alpha*size-1)/size;
			return;
		}
	}
	throw out_of_range(" Key is not present in the hash table for removal!");
}

void HashTable::update (pair<string, int> new_value){
	long long index = hash_str(new_value.first);
	for(vector<pair<string,int> >::iterator it = data[index]->begin(); it != data[index]->end(); ++it){
		if (it->first == new_value.first){
			it->second = new_value.second;
			return;
		}
	}
	throw out_of_range("Key not found for update!");
}

long long HashTable::hash_str(string str) const{
	int length = str.length();
	long long index = 0;
	for ( int i = length -1; i >= 0; i--){
		index += pow(29,i)*(str[length-i-1]);
	}
	index = index % size;
	return index;
}

void HashTable::resize(){
 	
	vector<pair<string,int> >** temp = new vector<pair<string,int> >*[2*size+1];
	for ( int i =0; i < 2*size+1; i++){
		temp[i] = new vector<pair<string,int> >;
	}
	int oldsize = size;
	double elements = alpha*size;
	size = 2*size + 1;
	for ( int i =0; i < oldsize; i++){
		for (vector<pair<string,int> >::iterator it = data[i]->begin(); it != data[i]->end(); ++it){
			   long long index = hash_str(it->first);
			   temp[index]->push_back(*it);
		}
	}

	for ( int i = 0; i < oldsize; i++){
		delete data[i];
	}
	delete[] data;
	data = temp;
	for ( int i =0; i < size; i++){
		data[i] = temp[i];
	}
	alpha = 1.0*elements/size;

}