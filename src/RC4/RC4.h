/**
 * RC4 Cryptographic Implementation
 * RC4.h
 * Purpose : encrypt and decrypt data
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.2
 * @date 11/10/2018
 */

#ifndef RC4PARALLEL_RC4_H
#define RC4PARALLEL_RC4_H

///Common Includes
#include "../Common/Includes.h"

class RC4 {
    public:
        /**
         * Constructor of RC4
         */
        RC4();

        /**
         * Initialize the indexes and permutation table encryption
         * @param key Key of the message
         * @param size Size of the key
         */
        void setKey(string key, long size);

        /**
         * Start the RC4 encryption/decryption
         * @param chunk Data chunk from the file
         */
        void execute(pair<int[2], unsigned char*>* chunk);

        /**
         * [Unsed] Calculate the indexes and permutation table encryption to a certain point for encryption/decryption texts parts
         * @param end End bound
         */
        void setIndexes(int end);

    private:
        /**
         * Calculate the initial values through the key in the permutation table encryption
         * @param key Key of the message
         */
        void ksa(unsigned char* key);

        /**
         * Swap the values on the permutation table encryption
         * @param i First value to swap
         * @param j Second value to swap
         */
        void swap(int i, int j);

        /**
         * RC4 encryption/decryption algorithm
         * @param text Text vector from the chunk
         */
        void prga(unsigned char* text, int size);

        /**
         * Permutation encryption table
         */
        unsigned char permutationTable[256];

        /**
         * Size of the encryption key
         */
        long keySize;

        /**
         * RC4 cipher indexes
         */
        int indexI, indexJ;
};


#endif //RC4PARALLEL_RC4_H
