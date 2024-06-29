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