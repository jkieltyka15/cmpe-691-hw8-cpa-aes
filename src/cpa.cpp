/**
 * File: cpa.cpp
 *
 * Implementation of power analysis attack on AES-128.
 */

// c++ libraries
#include <iostream>
#include <list>

// c libraries
#include <stdint.h>

// project c++ files
#include "ciphertext.hpp"

// project c files
#include "aes_sbox.h"
#include "correlation_coefficient.h"

// namespaces
using namespace std;
using namespace aes;

int main(int argc, char* argv[]) {

    list<Ciphertext> ciphers;

    // check for correct number of arguments
    if (5 != argc) 
    {
        cerr << "Incorrect number of arguments. Expecting: \'./cpa <inverse sbox file> <ciphertext file> <power analysis file> <output file>\'" << endl;
        return 1;
    }

    return 0;
}