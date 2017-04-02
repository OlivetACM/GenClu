#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool writemember(vector<string> name, string filename)
{
	ofstream outfile;
	outfile.open(filename);
	for(int i = 0; i < 3; i++)
	{
		outfile << name.at(i) << ',';
	}
}	
	
/*
int main()
{
	string fname = "john";
	string lname = "dohn";
	string idnum = "110224";
	string filename = "studentinfo.csv";		tested using this comented out code.
	vector<string> student_info;

	student_info.push_back(idnum);
	student_info.push_back(fname);
	student_info.push_back(lname);


	writemember(student_info, filename);
*/

	return 0;
}


