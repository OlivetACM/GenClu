#include <iostream>
#include <fstream>
#include <sstream>
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

void chomp(string &s){
    int pos;
    if((pos = s.find("\n")) != string::npos)
    	s.erase(pos);
}

vector<string> load_members(string filename){
	vector<string> members;
	string line;
	string header;
	ifstream rfile(filename.c_str());
	if(rfile.is_open()){
		getline(rfile, header);
		while(!rfile.eof()){
			string[] words = new string[3];
			rfile >> line;
			chomp(line);
			cout << line << endl;
			split(line, ',', words);
			members.push_back(words)
		}
	}
	rfile.close();
	return members;
}

int main(){
	vector<string> test = load_members("../members.csv");
	for(int i = 0; i < test.size(); i++)
		cout << test[i] << endl;
	return 0;
}
