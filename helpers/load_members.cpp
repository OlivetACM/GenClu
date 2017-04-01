#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

string[] load_members(string filename){
	string[] members = new string[];
	string line = '';
	int count = 0;
	ifstream rfile(filename.c_str());
	if(rfile.is_open()){
		while(!rfile.eof()){
			rfile >> line;
			// To be revised
			line = line.strip();
			member[count] = split(line, ',');
			count++;
		}
	}
	rfile.close();
	return members
}

