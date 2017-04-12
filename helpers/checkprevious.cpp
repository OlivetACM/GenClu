#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <dirent.h>

//using std::string;, using std::ctime;, using std::cout;
//using std::endl;, using std::map;
using namespace std;


int checkprevious()
{
	string present_day = "00000000"; //yyyymmdd
	string file_location = "";
	time_t now = time(0);
	char* dt = ctime(&now);
	vector<string> files;

//----------------------------------------------------------------------------
//this part of the code creats a takes the time I got from c time and peices together a yyymmdd
//that is stored in the present day variable.
	map<string, string> month//converts abreviated month part of ctime into its number form.
	{
		{"Jan", "01"},
		{"Feb", "02"},
		{"Mar", "03"},
		{"Apr", "04"},
		{"May", "05"},
		{"Jun", "06"},
		{"Jul", "07"},
		{"Aug", "08"},
		{"Sep", "09"},
		{"Oct", "10"},
		{"Nov", "11"},
		{"Dec", "12"},
	};
	map<string, string>::iterator itsa;		

	string day = "000";//where I will store "Mar"

	for(int i = 0; i < 3; i++)
	{
		day[i] = dt[4+i];//fils day with the apropriat letters.
	}

	itsa = month.find(day);//finds day in the map so that the conversion can begin.

	for(int i = 0; i < 4; i++)
	{
		present_day[i] = dt[20+i]; //puts the year into present_day 20170000
	}
	
	for(int i = 4; i < 6; i++)
	{
		present_day[i] = itsa->second[0 + (i-4)];//puts the month into present_day 20170400
	}

	for(int i = 6; i < 8; i++)
	{
		present_day[i] = dt[8+(i-6)];//puts the day into present_day 20170404.which will be our first part of our read in file.
	}
//-------------------------------------------------------------------------------------------
//This part of the code will peace together the rest of the file_location that is needed.
//for testing perpaces I aimed for 20170404/event1.csv, because I created a event1.csv in a directory 20170404.
//event1.csv is just the starting event the program will look for.
	file_location = "c:\\users/koryslaby/documents/code/s.ssum/acm projects/";//file location. will have to be edited.
	file_location = file_location + present_day;//adds the present day part 20170404.
	file_location = file_location + "\\";

	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (file_location.c_str())) != NULL) {
  	/* print all the files and directories within directory */
  		while ((ent = readdir (dir)) != NULL) {
  		  files.push_back(ent->d_name);
 		 }
 		 closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	
	for(vector<string>::iterator count = files.begin(); count < files.end(); count++)
	{
		
		cout << *count << endl;
		
	}

	return 0;

}



int main()
{
	checkprevious();


	return 0;
}






