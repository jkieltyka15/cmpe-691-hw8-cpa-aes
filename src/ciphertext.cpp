/**
 * File: ciphertext.cpp
 *
 * Implementation of ciphertext class.
 */

#include "ciphertext.hpp"

aes::Ciphertext::Ciphertext() {}

aes::Ciphertext::Ciphertext(Ciphertext* ciphertext) {
    for (int i = 0; AES_COL_LEN > i; i++) {
        for (int j = 0; AES_ROW_LEN > j; j++) {
            this->set_byte(i, j, ciphertext->get_byte(i,j));
        }
    }
}

bool aes::Ciphertext::set_byte(uint32_t col, uint32_t row, uint32_t val) {

    if (AES_COL_LEN < col || AES_ROW_LEN < row) {
        return false;
    }
    this->cipher[col][row] = (uint8_t)val;
    return true;
}

int32_t aes::Ciphertext::get_byte(uint32_t col, uint32_t row) {
    
    if (AES_COL_LEN < col || AES_ROW_LEN < row) {
        return -1;
    }
    return (int32_t)this->cipher[col][row];
}