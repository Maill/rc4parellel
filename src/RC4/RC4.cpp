/**
 * RC4 Cryptographic Implementation
 * RC4.cpp
 * Purpose : encrypt and decrypt data
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.2
 * @date 11/10/2018
 */

///Intern include
#include "RC4.h"

/**
 * Constructor of RC4
 */
RC4::RC4() = default;

/**
 * Initialize the indexes and permutation table encryption
 * @param key Key of the message
 * @param size Size of the key
 */
void RC4::setKey(string key, long size) {
    indexI = 0;
    indexJ = 0;
    keySize = size;
    for(int i = 0; i < 256; i++){
        permutationTable[i] = (unsigned char)i;
    }
    ksa((unsigned char *) key.c_str());
}

/**
 * Start the RC4 encryption/decryption
 * @param chunk Data chunk from the file
 */
void RC4::execute(pair<int, vector<unsigned char>>* chunk) {
    prga(&chunk->second);
}

/**
 * Calculate the initial values through the key in the permutation table encryption
 * @param key Key of the message
 */
void RC4::ksa(unsigned char *key) {
    int j = 0;
    for(int i = 0; i < 256; i++){
        j = (j + permutationTable[i] + key[i % keySize]) % 256;
        swap(i, j);
    }
}

/**
 * Swap the values on the permutation table encryption
 * @param i First value to swap
 * @param j Second value to swap
 */
void RC4::swap(int i, int j) {
    unsigned char swapedData = permutationTable[i];
    permutationTable[i] = permutationTable[j];
    permutationTable[j] = swapedData;
}

/**
 * RC4 encryption/decryption algorithm
 * @param text Text vector from the chunk
 */
void RC4::prga(vector<unsigned char>* text) {
    for (unsigned char &k : *text) {
        indexI = (indexI + 1) % 256;
        indexJ = (indexJ + permutationTable[indexI]) % 256;
        swap(indexI, indexJ);
        k = permutationTable[(permutationTable[indexI] + permutationTable[indexJ]) % 256] ^ k;
    }
}

/**
 * [Unsed] Calculate the indexes and permutation table encryption to a certain point for encryption/decryption texts parts
 * @param end End bound
 */
void RC4::setIndexes(int end) {
    for(int k = 0; k < end; k++) {
        indexI = (indexI + 1) % 256;
        indexJ = (indexJ + permutationTable[indexI]) % 256;
        swap(indexI, indexJ);
    }
}
