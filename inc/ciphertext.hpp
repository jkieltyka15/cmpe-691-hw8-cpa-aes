#ifndef _CIPHERTEXT_HPP_
#define _CIPHERTEXT_HPP_

#include <stdint.h>
#include <stdbool.h>

#define AES_COL_LEN 4
#define AES_ROW_LEN 4

namespace aes {

    class Ciphertext {

        private:
            uint8_t cipher[AES_COL_LEN][AES_ROW_LEN];

        public:

            Ciphertext();
            Ciphertext(Ciphertext* ciphertext);
        
            /**
             *  Sets a byte of the ciphertext.
             * 
             * @param col - Column of byte
             * @param row - Row of byte
             * @param val - Value to set byte to
             * @return True on success. Otherwise false 
             */
            bool set_byte(uint32_t col, uint32_t row, uint32_t val);

            /**
             * Gets a byte of the ciphertext.
             * 
             * @param col - Column of byte
             * @param row - Row of byte
             * @return Value of ciphertext byte. Otherwise -1 
             */
            int32_t get_byte(uint32_t col, uint32_t row);
    };
}

#endif // _CIPHERTEXT_HPP_