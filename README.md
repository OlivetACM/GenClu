# GenClue

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

_To be expanded_...

## Compiling GenClu

_To be expanded_

## What and How Functions Work

### Helper Functions
There are several backend helper functions which work to compress the amount of code which might otherwise be shoved into the gui as a methods. In an effort to keep the gui clean an easy to read we have seperated our code into three sections:
1. Headers
2. Helpers
3. GUI
The functions and purposes for all of these things will be described below. The exact descriptions for each will be moved into the function sometime after completion. 

### Headers
These are just the header files for the project. Nothing special to mention.

### Helpers

1. ```load_members(String filename)```
 * This function has two purposes. The fist is to load in the members.csv data so that the program can start taking attendance. The other purpose is to readin old attendance data so it can be adjusted in memory and then later spit back into a truncated file. DOES NOT REMOVE HEADER IN MEMORY. The csv header is left as the first entry in the vector!
 * Needs some refactoring.
2. ```memberexists(std::vector<std::vector<string>> members, string idnum)```
 * This function is just a specialized linear search function. It combs through the members vector search for the given string idnum. If found it returns the integer location in the outmost vector of the member in question. Otherwise it returns -1.
3. ```checkprevious(String folder)```
 * Scans the attendance for to determine if there were previous events and if so what the names of those previous events were. If there were no previous events check previous should return null.

### QT

_To be expanded_...
