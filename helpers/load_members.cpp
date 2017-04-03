#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <iterator>



std::vector<std::vector<std::string> > load_members(std::string filename){
	//std::vector<std::string> member;
	std::vector<std::vector<std::string> > whole;
	std::string line;
	std::ifstream rfile;
	rfile.open(filename.c_str());
		while (getline(rfile, line)){
			std::vector<std::string> member;
			std::stringstream strstrm(line);
			std::string word = ""; 
			while (getline(strstrm,word, ',')) member.push_back(word);
			whole.push_back(member);
		}
	rfile.close();
	return whole;
 }

int main(){
	std::vector<std::vector<std::string> > test = load_members("../members.csv");
	for(int j = 0; j < test.size(); j++){
		for(int i = 0; i < test.at(j).size(); i++){
			std::cout << test.at(j).at(i);
		}
		std::cout << std::endl;
	}
	return 0;
}
