/**
 * File: cpa.cpp
 *
 * Implementation of power analysis attack on AES-128.
 */

// c++ libraries
#include <iostream>
#include <fstream>
#include <list>
#include <string>

// c libraries
#include <stdint.h>
#include <stdbool.h>

// project c++ files
#include "ciphertext.hpp"

// project c files
#include "aes_sbox.h"
#include "correlation_coefficient.h"

// namespaces
using namespace std;
using namespace aes;

int main(int argc, char* argv[]) {

    char* inverse_sbox_file_path = nullptr;
    char* cipher_file_path = nullptr;
    char* power_analysis_file_path = nullptr;
    char* output_file_path = nullptr;

    ifstream cipher_file;
    ifstream power_analysis_file;
    ofstream output_file;

    Ciphertext cipher;
    list<Ciphertext> ciphers;

    // check for correct number of arguments
    if (5 != argc) 
    {
        cerr << "Incorrect number of arguments. Expecting: \'./cpa <inverse sbox file> <ciphertext file> <power analysis file> <output file>\'" << endl;
        return 1;
    }

    // give arguments nice names
    inverse_sbox_file_path = argv[1];
    cipher_file_path = argv[2];
    power_analysis_file_path = argv[3];
    output_file_path = argv[4];

    // open file streams
    cipher_file.open(cipher_file_path, ifstream::in);
    power_analysis_file.open(power_analysis_file_path, ifstream::in);
    output_file.open(output_file_path, ofstream::out);

    // load inverse sbox
    inverse_sbox_load(inverse_sbox_file_path);

    // load ciphertext
    for (bool eol = false; !eol;) {
        for (int i = 0; AES_COL_LEN > i; i++) {
            for (int j = 0; AES_ROW_LEN > j; j++) {

                char cipher_byte_str[4];
                int cipher_byte_int = 0;
                if (!(cipher_file >> cipher_byte_str)) {
                    eol = true;
                    break;
                }
                cipher_byte_int = stoi(cipher_byte_str);
                cipher.set_byte(i, j, (uint8_t)cipher_byte_int);
            }
            if (eol) {
                break;
            }
        }
        if (!eol) {
            ciphers.push_front(cipher);
        }
    }
    cipher_file.close();

    return 0;
}