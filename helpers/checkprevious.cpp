#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>

//using std::string;, using std::ctime;, using std::cout;
//using std::endl;, using std::map;
using namespace std;


int checkprevious()
{
	string present_day = "00000000"; //yyyymmdd
	string file_location = "";
	time_t now = time(0);
	char* dt = ctime(&now);

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

	file_location = file_location + present_day;//adds the present day part 20170404.
	file_location = file_location + "/";//20170404/
	file_location = file_location + "event1.csv";//20170404/event1.csv
	ifstream file(file_location);//searchs for the now complete file location. or so the one I tested for it can be changed.

	if(file.is_open())//This next part will check to see if there is more that one event in the present day directory(20170404).
	{
		string tempfilecheck = file_location;
		for(int i = 1; i < 10; i++)
		{
			//----------------------------
			stringstream ss;	
			ss << i;				//used in integer to string conversion.
			string nums = ss.str();
			//-----------------------------
			tempfilecheck[14] = nums[0];//changes the event1.csv into event2.csv or 3,4,5,etc. 
			ifstream file2(tempfilecheck);
			if(file2.is_open())
			{
				//does nothing so it goes through the for loop again and checks for anothe event.csv file.
			}else{
				//cout << "there are curently " << (i-1) << " events made today" << endl;//tells the user how many events there are.
				return (i-1);
				i = 100;//ends the for loop.
			}
		}

			
	}else{
		//cout << "there is no event for today yet" << endl;
		return 0;
	}
}



int main()
{
	cout << checkprevious();


	return 0;
}






