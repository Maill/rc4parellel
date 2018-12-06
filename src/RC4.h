//
// Created by olivier on 10/11/18.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef RC4PARALLEL_RC4_H
#define RC4PARALLEL_RC4_H


class RC4 {
    public:
        RC4();

        void setKey(std::string key, int size);

        std::pair<int, unsigned char*> encrypt(std::string in, int size);

        void setIndexes(int end);

    protected:
        void ksa(unsigned char* key);

        void swap(int i, int j);

        std::pair<int, unsigned char*> prga(unsigned char *text, int size);

        unsigned char permutationTable[256];

        int keySize, indexI, indexJ;
};


#endif //RC4PARALLEL_RC4_H
