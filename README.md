# GenClu

## Table of Contents

1. [Purpose](#purpose)
2. [Customizing GenClu](#adapting-genclu-for-your-group)
3. [Compiling GenClu](#compiling-genclu)
4. [Current Status Remarks](#current-status)
5. [How To Use](#how-to-use)
    * [General Use](#general-use)
    * [Additional Features](#additional-features)
    * [Problems](#problems)


## Purpose
GenClu is a very simple attendance program which uses a QT frontend. The idea is that there are many very complex and attendance takers out there on the web but none that just do "the basics". GenClu is here to fix this. The features will be intentionally limited and small but, in doing so, they should perfect and flawless. 

Originally purposed by the Olivet College Sigma Zeta chapter, this project project was developed by the Olivet College chapter  of the Association for Computing Machinery to assist them with their massive attendance numbers. 

## Adapting GenClu for Your Group

There are several hard coded things that exist in GenClu. Members only have three criteria through which they can be categorized. This is because our college ids have the following data on their magnetic strip:
```
;12345?
%12345?
...
```
Where the starting character is denoted by either a ; or a %. If this is not the same for you or your college / id system stores other data you will need to adjust the delimiters through which the swipe can be detected. 

This behavior can be changed in `keyPressEvent` inside of MainWindow. Essentially the starting character kicks off a timer where all the input is read in from the card reader and then when the final marker, in our case the "?", is read in, `keyPressEvent` just discards the extra input.

## Compiling GenClu

This program revolves heavily around QT 5.8 and a CPP compiler. 
The source code isn't written to be compatible with G++ however that being said, there isn't any Windows specific code that would prevent the program from compiling using G++.

First you need to run QMake to generate all the MOC files.
```
> qmake genclu.pro
```
To compile the program in release mode use the following command to generate an executable.
```
> nmake release
```
Then if you want to make the application deployable you will have to run another Qt utility called windeployqt. So from there run the following.
```
> nmake clean
> cd release
> windeployqt --release GenClu.exe
```

Then feel free to put the files in a zip or an installer to distribute the executable and the resources to end-users.
We've gone through and bundled the application for convience and flash-drive style ease of use.
To bundle the executable we used Enigma Virtual Box.
Stay tuned!

## How to Use

### General Use
1. Download the most recent release version of the program [here](https://github.com/OlivetACM/GenClu/releases/).
    * If you're choosing to compile your own version follow those steps before proceeding.
2. Put GenClu\_boxed.exe wherever you want on your computer. My suggestion would be to give it's own folder on your desktop or just give GenClu its own flash drive.
3. Run the executable, traditionally by double-clicking.
4. Select either "New Event" or "Previous Event". 
    * Make sure you have the right radio button selected! (The circle dot that fills itself when clicked)
    * GenClu will generate an attendance folder in the same folder it lives in. It will also generate a folder with the name of todays date in the form yyy.MM.dd therefore May 7th, 1994 => 1994.05.07
    * Inside this folder will be the the event files which will be either CSV or XLSX format. Currently only CSV is implemented. Keep in mind that either of these files can be opened in MCS Excel or Libre Calc without any issues.
5. Use an Card Reader to swipe an ID or enter the data manually.
    * If you choose to swipe an id using a Card Reader you will still have to input FirstName and LastName by hand. This should only ever happen once. Future swipes will automatically use the previously entered data.
    * When you manually enter data after swiping you will notice that the ID field cannot be changed. THIS IS WORKING AS INTENDED. That field is filled with data on the card. It is the de facto identifier whether or not the swiper understands that that is their true id. A "True ID" field may be added in the future to workaround this issue despite it not being a fault of the program.
    * When you FULLY manually enter data (id as well) this is just as technically effective as the card swipe and runs through the jumps through the same hoops as swiping.
    * If members.csv does not exist when the program recieves its first bits of data it will create the CSV in its personal directory. Don't delete this file unless you want to manually enter data a ton.
6. If your swipe was successful then you will see a greeting like "Hello FirstName LastName!" right above the buttons. 
    * If you swipe a member who has already been swiped for that event then you'll see something along the lines of "MEMBER ALREADY SWIPED".
    * If the programd detects a bad swip then you will be prompted to either do a full manual entry OR click Cancel and reswipe the card.
7. When done just close the program!

### Additional Features
* Using previous events.
    * If you're going to edit previous events the understand that GenClu will only allow you change events that happened that day. If you need to edit attendance files from May 9th and today is May 10th GenClu will not display any of the May 9th files for editing.
    * You can however edit previous days by hand using any basic text editor or spreadsheet editor. Please do note that attendance is logged in the order of `LastName,FirstName,IDNumber\n` kind of way. Any variations of this might break GenClu.
* Changing Files
    * You can create another event or edit another event without closing GenClu. Just click the "Change File" button and the "SELECT ATTENDANCE FILE" prompt will reappear. Any members that were previously marked as "present" will be loaded correctly.

### Problems
These aren't "bugs" exactly but just things that were never handled in the first place.
1. Make sure that when you enter someone's information manually or swipe their card that you don't have the attendance file open in excel. This will cause the program to crash. It's a not huge deal because you can reopen the program and then have it reopen the file it was using previously. So if you need to access the attendance file, simply don't enter anyone manually or swipe with their card while the attendance file is open but be sure to close excel or whatever you're using to view the file before swiping/entering again.

2. Alphabetical ordering of the attendance file. The reason why is complex. Basically the only thing we can do to fix this is to have the program reorder the attendance file after it's been closed or switches files. We can add a button to do it as well. 
