//linear search method to confirm that member exsits
#include <iostream>
#include <string>
#include <vector>
#include "memberexists.h"

//using std::vector; using std::string; NONE OF THESE

int memberexists(std::vector<std::vector<std::string>> members, std::string idnum){
//Takes a Vector of a String Vector
//Returns index at with idnum is found, or -1 if idnum is not found
        for(int i = 0; i < members.size(); i++){
            
            if((members.at(i).at(0)) == idnum){
                return i;
            }
        }
        return -1;
}


//Working test run
/*
int main()
{
    std::vector<std::vector<std::string>> members;
    std::vector<std::string> memtest;
    std::vector<std::string> testmem;

    std::string idnum = "110222";

    memtest.push_back({"222011"});
    memtest.push_back({"Name"});
    memtest.push_back({"Generic"});

    members.push_back({memtest});

    testmem.push_back({"110222"});  //Add info to inner vector
    testmem.push_back({"J"});       //Sample info, form: (ID, Last Name, First Name)
    testmem.push_back({"Ryan"});

    members.push_back({testmem});   //Add inner vector to outer vector

    std::cout<<memberexists(members, idnum); //Returns 1 for this example

    return 0;
}
*/
