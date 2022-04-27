# SRT file parser in C

![System](https://img.shields.io/badge/System-Android_TERMUX-47D167?style=for-the-badge&logo=android)

![Language](https://img.shields.io/badge/language-c-00599c?style=for-the-badge&logo=c&logoColor=white)

![Status](https://img.shields.io/badge/status-concluded-87D935?style=for-the-badge)

SRT File parser in C. This program gets a srt file as a command line argument. The main purpose is to be able to change the time of the subtitles, entering a new value in **seconds**. 

Currently, the option 1 - "Parse" shifts the time, while creating a new file "Outfile.srt", with the updated time. The option 2 - "Print File" just prints the file, and 3 - "Exit" leaves the program.

# Usage

After building the executable "Clegend", the target file is inserted by passing as a reference in the command line:

````
// On Linux, passing the sample file in the src folder

[user@DESKTOP C-SRT-FileParser]$ ./clegend src/IronMan.srt
````
## Menu

````
Openning File : src/IronMan.srt

        1 - Parse
        2 - Print File
        6 - Exit
````
## Parse

````
1  // Chosen option

How many seconds to shift ? : 59
````
## Comparison IN and OUT files

````
// Input File

897
00:59:10,365 --> 00:59:12,591
No. No, absolutely not.
It'll give me a bone to throw the boys
====================================================

// Output File

897
01:00:09,365 --> 01:00:11,591
No. No, absolutely not.
It'll give me a bone to throw the boys

````

This code is a challenge made by my friend [Jose Rogerio](https://github.com/almeidajr).

# Notes 

- On the branch "DEV" there is a preliminar implementation of the full parser, wich can turn the entire file into a List of sequences. Currently only working with the "file.srt". Caracther comparisson leads to segmentation faults.

- **(Fixed - Lists Removed)** The sequence List is a queue, where the first is always frist, and new members are put in the end of the list.(Last In First Out)
- **(Fixed - Lists Removed)** "first" pointer and "last" pointer keeps track of the data in their respective positions.
- **(Fixed - No dynamic allocation)** Memory is not reallocated, or liberated, Possible memory leak issue.

# To-do
- [X] Keep track of dynamic allocated variables - No Leaks or Runtime Errors, checked with Valgrind.
- [X] Implement Parsing function in the menu - Option 1.
- [X] Implement UpdateTime function - Got Called GhangeTimestamp.

# Valgrind Analisys
Command:
````
[user@DESKTOP C-SRT-FileParser]$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./clegend src/IronMan.srt
````
Result, for 59 sec time shift