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
