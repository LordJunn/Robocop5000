/* *********************************************************************
PROGRAM : print.h
COURSE: OOPDS
TRIMESTER: 2410
LECTURE SESSION: TC1L
TUTORIAL SESSION: TT2L
GROUP: 3

Member 1
Name: Chee Rui
ID: 1211112287

Member 2
Name: Andrew Wee Hong Jun
ID: 1211108270

Member 3
Name: Mei Yong Peng
ID: 1211109159

Member 4
Name: Low Junn Kit
ID: 1211111305

Member 5
Name: Fong Kai Chun
ID: 1211108430

Member 6
Name: Chan Ka Ken 
ID: 1211109440

********************************************************************* */


#ifndef PRINT_H
#define PRINT_H

#include <iostream>

extern std::ofstream resultfile;


// Function prototype declaration
template<typename T>
void print_to_both(const T& arg) {
    std::cout << arg;
    resultfile << arg;
}

// Recursive function template to print multiple arguments consecutively and also to put it into resultfile
template<typename T, typename... Args>
void print(const T& arg, const Args&... args) {
    print_to_both(arg);
    (..., print_to_both(args)); //helps to prints recursively
}

#endif