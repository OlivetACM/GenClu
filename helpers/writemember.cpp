#include <iostream>
#include <fstream>
#include <string>
bool writemember(String Fname, String Lname, String Idnum, String Filename){
	ofstream outfile;
	outfile.open(Filename);
	outfile << Idnum << ',' << fname << ',' << Lname << endl;
	return true;
}