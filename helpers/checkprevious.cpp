#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>

//using  std::string;, using std::ctime;
using namespace std;


void checkprevious()
{
	string present_day = "00000000"; //yyyymmdd
	string file_location = "";
	time_t now = time(0);
	char* dt = ctime(&now);

	map<string, string> month
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

	string day = "000";

	for(int i = 0; i < 3; i++)
	{
		day[i] = dt[4+i];
	}

	itsa = month.find(day);

	for(int i = 0; i < 4; i++)
	{
		present_day[i] = dt[20+i]; // year
	}
	
	for(int i = 4; i < 6; i++)
	{
		present_day[i] = itsa->second[0 + (i-4)];//month
	}

	for(int i = 6; i < 8; i++)
	{
		present_day[i] = dt[8+(i-6)];//day
	}

	file_location = file_location + present_day;
	file_location = file_location + "/";
	file_location = file_location + "event1.csv";
	ifstream file(file_location);

	if(file.is_open())
	{
		string tempfilecheck = file_location;
		for(int i = 1; i < 100; i++)
		{
			tempfilecheck[14] = str(i);// should run through and check for more than one event file
			ifstream file2(tempfilecheck);//I have to figure out how to turn a int into string and will be all set.
			cout << tempfilecheck << endl;
			if(file2.is_open())
			{
			}else{
				cout << "there are curently " << i << " events made today" << endl;
				i = 100;
			}
		}

			
	}else{
		cout << "there is no event for today yet" << endl;
	}


}

int main()
{
	checkprevious();


	return 0;
}




