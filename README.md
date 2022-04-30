# SRT file parser in C

![System](https://img.shields.io/badge/System-Android_TERMUX-47D167?style=for-the-badge&logo=android)

![Language](https://img.shields.io/badge/language-c-00599c?style=for-the-badge&logo=c&logoColor=white)

![Status](https://img.shields.io/badge/status-concluded-87D935?style=for-the-badge)

SRT File parser in C. This program gets a srt file as a command line argument. The main purpose is to be able to change the time of the subtitles, entering a new value in **seconds** or in **milliseconds**. 

Currently, the option 1 - "Parse in seconds" shifts the time in seconds, while creating a new file "Outfile.srt", with the updated time. The option 2 - "Parse in milliseconds" shifts the time in milliseconds. Option 3 - "Print File" just prints the source file, and 6 - "Exit" leaves the program.

# Usage

After building the executable "Clegend", the target file is inserted by passing as a reference in the command line:

````
// On Linux, passing the sample file in the src folder

[user@DESKTOP C-SRT-FileParser]$ ./clegend src/IronMan.srt
````
## Menu

````
Openning File : src/IronMan.srt

Choose an Option:
        1 - Parse in seconds
        2 - Parse in milliseconds
        3 - Print File
        6 - Exit
````
## Parse

````
1  // Chosen option

How many seconds to shift ? : 59

        Creating Outfile.srt...

        Outfile.srt created.

====================================================
2  // Chosen option

How many milliseconds to shift ? : 59000

        Creating Outfile.srt...

        Outfile.srt created.
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

- Added help message for invalid inputs or NULL input.
- Changed Menu, added option to shift milliseconds.
- Fixed Timestamp function - Values multiple of 60 would give +1 to hour value, and minutes would not be increased.
- Timestamp function fixed, so negative values can be entered, and reverse the timestamp. 
- On the branch "DEV" there is a preliminar implementation of the full parser, wich can turn the entire file into a List of sequences. Currently only working with the "file.srt". Caracther comparisson leads to segmentation faults.
- **(FIXED - ChangeTimestamp updated)** Currently only shifting time **fowards**.
- **(FIXED - Lists Removed)** The sequence List is a queue, where the first is always frist, and new members are put in the end of the list.(Last In First Out)
- **(FIXED - Lists Removed)** "first" pointer and "last" pointer keeps track of the data in their respective positions.
- **(FIXED - No dynamic allocation)** Memory is not reallocated, or liberated, Possible memory leak issue.

# To-do
- [X] Keep track of dynamic allocated variables - No Leaks or Runtime Errors, checked with Valgrind.
- [X] Implement Parsing function in the menu - Option 1.
- [X] Implement UpdateTime function - Got Called GhangeTimestamp.
- [X] Fix Timestamp Function - Now working fowards and reverse in time.
- [X] Give option to update time in milliseconds.

# Valgrind Analisys
Command:
````
[user@DESKTOP C-SRT-FileParser]$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./clegend src/IronMan.srt
````
Result, for 59 sec time shift:
````
==6218== HEAP SUMMARY:
==6218==     in use at exit: 0 bytes in 0 blocks
==6218==   total heap usage: 6 allocs, 6 frees, 11,184 bytes allocated
==6218== 
==6218== All heap blocks were freed -- no leaks are possible
==6218== 
==6218== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
````