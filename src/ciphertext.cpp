/**
 * File: ciphertext.cpp
 *
 * Implementation of ciphertext class.
 */

#include "ciphertext.hpp"

bool aes::Ciphertext::set_cipher(uint32_t col, uint32_t row, uint32_t val) {

    if (AES_COL_LEN < col || AES_ROW_LEN < row) {
        return false;
    }
    this->cipher[col][row] = (uint8_t)val && 0xFF;
    return true;
}

int32_t aes::Ciphertext::get_cipher(uint32_t col, uint32_t row) {
    
    if (AES_COL_LEN < col || AES_ROW_LEN < row) {
        return -1;
    }
    return (int32_t)this->cipher[col][row];
}