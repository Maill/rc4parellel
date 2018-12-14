/**
 * File Accessor for reading and writing in different files
 * FileAccessor.h
 * Purpose : Read data in an input file and write data to an output file
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 10/12/2018
 */

#ifndef RC4PARALLEL_FILEACCESSOR_H
#define RC4PARALLEL_FILEACCESSOR_H

///Common Includes
#include "../Common/Includes.h"

class FileAccessor {
    public:
        /**
         * Constructor of FileAccessor
         * @param inputFile Path of the input file
         * @param outputFile Path of the output file
         */
        FileAccessor(const string &inputFile, const string &outputFile);

        /**
         * Destructor of FileAccessor
         */
        ~FileAccessor();

        /**
         * Get the next chunk of data of the input file
         * @return A pair with the position of the pointer on the beginning of the read and a vector that encapsulate the data
         */
        pair<int[2], unsigned char*> getNextChunk();

        /**
         * Write the data of the chunk into the output file
         * @param chunk Data chunk to be written
         */
        void writeChunk(pair<int[2], unsigned char*> chunk);

        /**
         * Data length of the input file
         */
        int inputFileLength;

    private:
        /**
         * Lock of the input file
         */
        mutex mutexReadFileOperation;

        /**
         * Lock of the output file
         */
        mutex mutexWriteFileOperation;

        /**
         * File pointer to the input file
         */
        ifstream inputFile;

        /**
         * File pointer to the output file
         */
        ofstream outputFile;
};

#endif //RC4PARALLEL_FILEACCESSOR_H
