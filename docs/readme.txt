University of Maryland, Baltimore County 
CMPE/ENEE 491/691 
Hardware Security 
Spring 2023 
HW 8: Power Analysis Attack on AES-128
Jordan Kieltyka

Prerequisites: g++ with C++11 compiler using Linux

Build and Test:
    1) To build, use command 'make cpa' in the 'project root' directory.
    2) To perform attack, use command:
       './build/bin/cpa ./res/inverse-sbox.txt ./data/cipher.txt ./data/power.txt ./data/round10key.txt' 
       in the 'project root' directory.
    3) Output will be in 'round10key.txt' in the 'data' directory.

Notes
    * Simply using the command 'make' will build everything.
    * To clean the 'build/bin' directory, use the command 'make clean'.
    * This program takes awhile to run since it is not optomized. Standard output is printed out to show program is not hanging.