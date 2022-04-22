# SRT file parser in C

![System](https://img.shields.io/badge/System-Android_TERMUX-47D147?style=for-the-badge&logo=android)

![Language](https://img.shields.io/badge/language-c-00599c?style=for-the-badge&logo=c&logoColor=white)

SRT File parser in C. This program gets a srt file as a command line argument. The main purpose is to be able to change the time of the subtitles, entering a new value. 

Currently, the program has options of parse the file into a list of sequences, Print the file and exit.

This code is a challenge made by my friend [Jose Rogerio](https://github.com/almeidajr).

# Notes 

- The sequence List is a queue, where the first is always frist, and new members are put in the end of the list.(Last In First Out)
- "first" pointer and "last" pointer keeps track of the data in their respective positions.
- Memory is not reallocated, or liberated, Possible memory leak issue.

# To-do
- [ ] Keep track of dynamic allocated variables
- [ ] Implement Parsing function in the menu
- [ ] Implement UpdateTime function
