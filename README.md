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

This behavior can be changed in `keyPressEvent` inside of MainWindow. Essentially the starting character kicks off a timer where all the input is read in from the card reader and then when the final marker, in our case the "?", is read in, `keyPressEvent` just discards the extra input.

## Compiling GenClu

This program revolves heavily around QT 5.8 and a CPP compiler. 
The source code isn't written to be compatible with G++ however that being said, there isn't any Windows specific code that would prevent the program from compiling using G++.

First you need to run QMake to generate all the MOC files.
```
> qmake genclu.pro
```

Then a simple make command. Currently the program only compiles for debug and not release. 
To compile it for debug use
```
> nmake
```

To compile for release change the following line in genclu.pro
```
CONFIG += qt debug console
```
To
```
CONFIG += qt release console
```

Then run qmake so that it updates the Makefile. Then finally just run nmake.
```
> nmake
```


## What and How Functions Work

### Headers

### Helpers

### Windows & Why/How They Work

## Current Status

Currently the program requires a lot of error checking. What if a file is already open? What if the user requests a new event file using a filename that already exists? These sorts of cases are not handles by the progam. I would call the program frail at best. It works but only if everything goes absolutely according to plan. This often isn't the case for most software so this situation needs to be corrected.

The excelt file format should be available as there have been options added that will allow the program to write using XLSX format. However there have been problems trying to integrate exterior LIBs into our project. Stay tuned for a solution to this.
