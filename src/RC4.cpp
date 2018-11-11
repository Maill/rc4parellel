//
// Created by olivier on 10/11/18.
//

#include "RC4.h"

RC4::RC4() {

}

void RC4::setKey(std::string key, int size) {
    indexI = 0;
    indexJ = 0;
    keySize =size;
    for(int i = 0; i < 256; i++){
        permutationTable[i]=(unsigned char)i;
    }
    ksa((unsigned char *) key.c_str());
}

std::string RC4::encrypt(std::string in, int size) {
    return prga((unsigned char*) in.c_str(), size);
}

void RC4::ksa(unsigned char *key) {
    int j = 0;
    for(int i = 0; i < 256; i++){
        j = (j + permutationTable[i] + key[i % keySize]) % 256;
        swap(permutationTable, i, j);
    }
}

void RC4::swap(unsigned char data[], int i, int j) {
    unsigned char swapedData = data[i];
    data[i] = data[j];
    data[j] = swapedData;
}

std::string RC4::prga(unsigned char *text, int size) {
    char* cipher = (char*) malloc(size + 1);
    for(int k = 0; k < size; k++){
        indexI = (indexI + 1) % 256;
        indexJ = (indexJ + permutationTable[indexI]) % 256;
        swap(permutationTable, indexI, indexJ);
        cipher[k] = permutationTable[(permutationTable[indexI] + permutationTable[indexJ]) % 256] ^ text[k];
    }
    std::string ret = std::string(cipher);
    free(cipher);
    return ret;
}
