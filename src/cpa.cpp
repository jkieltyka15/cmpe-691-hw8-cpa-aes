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

// constants
#define POWER_TRACE_LINES         7500
#define POWER_TRACE_INTS_PER_LINE 2500

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

    list<list<Ciphertext>> hypo_int_vals;
    list<list<int>> hypo_power_traces;

    list<list<int>> power_traces;

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
            ciphers.push_back(cipher);
        }
    }
    cipher_file.close();

    // load power analysis
    for (int i = 0; POWER_TRACE_LINES > i; i++) {
        list<int> power_trace_line;
        for (int j = 0; POWER_TRACE_INTS_PER_LINE > j; j++) {
            char power_trace_str[4];
            power_analysis_file >> power_trace_str;
            power_trace_line.push_back(stoi(power_trace_str));
        }
        power_traces.push_back(power_trace_line);
    }
    power_analysis_file.close();

    // calculate hypthetical intermediate values
    for (auto ciphertext = ciphers.begin(); ciphertext != ciphers.end(); ciphertext++) {

        list<Ciphertext> hypo_vals;

        // perform inverse AES round for every key byte value
        for (int key = 0; 256 > key; key++) {

            Ciphertext hypo_val = Ciphertext(*ciphertext);

            // perform key xor
            for (int i = 0; AES_COL_LEN > i; i++) {
                for (int j = 0; AES_ROW_LEN > j; j++) {
                    hypo_val.set_byte(i, j, (uint8_t)((uint8_t)hypo_val.get_byte(i, j) ^ (uint8_t)key));
                }
            }

            // perform row shift
            for (int j = 0; AES_ROW_LEN > j; j++) {
                for (int shifts = 0; j > shifts; shifts++) {
                    uint8_t tmp = (uint8_t)hypo_val.get_byte(AES_COL_LEN - 1, j);
                    for (int i = AES_COL_LEN - 1; 0 < i; i--) {
                        hypo_val.set_byte(i, j, (uint8_t)hypo_val.get_byte(i - 1, j));
                    }
                    hypo_val.set_byte(0, j, tmp);
                }
            }

            // perform inverse sbox
            for (int i = 0; AES_COL_LEN > i; i++) {
                for (int j = 0; AES_ROW_LEN > j; j++) {
                    hypo_val.set_byte(i, j, inverse_sbox_get((uint8_t)hypo_val.get_byte(i, j)));
                }
            }

            hypo_vals.push_back(hypo_val);
        }

        hypo_int_vals.push_back(hypo_vals);
    }
    ciphers.clear();

    // calculate hypothetical power consumption values
    for (auto int_ciphers = hypo_int_vals.begin(); int_ciphers != hypo_int_vals.end(); int_ciphers++) {

        list<int> hypo_power_trace;

        for (auto int_cipher = int_ciphers->begin(); int_cipher != int_ciphers->end(); int_cipher++) {
            for (int i = 0; AES_COL_LEN > i; i++) {
                for (int j = 0; AES_ROW_LEN > j; j++) {
                    hypo_power_trace.push_back(hw(int_cipher->get_byte(i,j)));
                }
            }
        }
        hypo_power_traces.push_back(hypo_power_trace);
    }
    hypo_int_vals.clear();

    // arrayify power consumptions values
    
    // create correlation array

    // detrmine key


    // cleanup
    output_file.close();

    return 0;
}