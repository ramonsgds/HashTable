#include <iostream>
#include "heap.h"
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <stdexcept>
using namespace std;


void backtrace(map<string,string>& predecessors, vector<string>& results, string s){
	if (predecessors.find(s) == predecessors.end()){
		results.push_back(s);
		return;
	}
	string pred = predecessors.find(s)->second;
	backtrace(predecessors, results, pred);
	results.push_back(s);
}

int main(int argc, char* argv[]){

	if (argc != 4){
		cout << "Error: Wrong number of arguments!" << endl;
		return -1;
	}
	vector<string> results;
	map<string,string> predecessors;
	vector<string> myvector;
	vector<string> closed_list;
	string startingword(argv[1]);
	transform(startingword.begin(),startingword.end(),startingword.begin(), ::tolower);
	string endingword(argv[2]);
	transform(endingword.begin(),endingword.end(),endingword.begin(), ::tolower);
	ifstream ifile(argv[3]);

	if (ifile.fail()){
		return -1;
	}

	int n = 0;
	ifile >> n;
	if ( n == 0){
		return -1;
	}

	MinHeap open_list_heap(2); //Check if there is a specific value for d.

	for ( int i =0 ; i < n; i++){
		string holder = "";
		ifile >> holder;
		transform(holder.begin(),holder.end(),holder.begin(), ::tolower);
		if (holder.length() == startingword.length()){
			myvector.push_back(holder);
		}
	}	

	open_list_heap.add(startingword,0);
	
	while(!open_list_heap.isEmpty()){

		string s = open_list_heap.peek();
		open_list_heap.remove();
		closed_list.push_back(s);
		if (s == endingword){
			backtrace(predecessors,results, s);
			break;
		}
		else{
			for ( unsigned int i = 0; i < myvector.size(); i++){
				 int diff = 0;
				for (unsigned int j =0; j < myvector[i].size(); j++){
					if ( myvector[i][j] != s[j]){
						diff++;
					}
				}
			
				if (diff == 1 && find(closed_list.begin(),closed_list.end(), myvector[i]) == closed_list.end()){
					 int h = 0;
					 int g = 0;
					for ( unsigned int j = 0; j < myvector[i].size(); j++){
						if ( myvector[i][j] != endingword[j]){
							h++;
						}
						if (myvector[i][j] != startingword[j]){
							g++;
						}
					}
					 int f = g + h;
					 int priority = f*(myvector[i].size()+1) + h;

					try {
						open_list_heap.update(myvector[i],priority);
					}

					catch (out_of_range& e){
						open_list_heap.add(myvector[i],priority);
						predecessors.insert(pair<string,string>(myvector[i],s));
					}
			
				}
			}
		}
	}

	for (map<string,string>::iterator it = predecessors.begin(); it != predecessors.end(); ++it){
		cout << it->first << " : " << it->second << endl; 
	}

	cout << "******-----******" << endl;
	for ( vector<string>::iterator it = results.begin(); it != results.end(); ++it){
		cout << *it << endl;
	}
	cout << "******-----******" << endl;
	for ( vector<string>::iterator it = closed_list.begin(); it != closed_list.end(); ++it){
		cout << *it << endl;
	}
	cout << "-----------------" << endl;
	cout << "Number of expansions: " << closed_list.size() - 1 << endl;
	
	return 0;
}