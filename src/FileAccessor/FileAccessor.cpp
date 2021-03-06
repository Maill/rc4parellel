/**
 * File Accessor for reading and writing in different files
 * FileAccessor.cpp
 * Purpose : Read data in an input file and write data to an output file
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 10/12/2018
 */

///Intern include
#include "FileAccessor.h"

/**
 * Constructor of FileAccessor
 * @param pathInputFile Path of the input file
 * @param pathOutputFile Path of the output file
 */
FileAccessor::FileAccessor(const string &pathInputFile, const string &pathOutputFile) {
    //Init file accessors
    this->inputFile = ifstream(pathInputFile, ios::binary | ios::ate);
    this->outputFile = ofstream(pathOutputFile, ios::binary);

    //Init variables
    this->inputFileLength = static_cast<int>(this->inputFile.tellg());

    //Return to the beginning of the input file
    this->inputFile.seekg(0, ios::beg);
}

/**
 * Get the next chunk of data of the input file
 * @return A pair with the position of the pointer on the beginning of the read and a vector that encapsulate the data
 */
pair<int[2], unsigned char*> FileAccessor::getNextChunk() {
    //Locking the access for the other threads
    lock_guard<std::mutex> lock(this->mutexReadFileOperation);

    pair<int[2], unsigned char*> chunk = pair<int[2], unsigned char*>();

    //Initialize data
    chunk.first[0] = static_cast<int>(this->inputFile.tellg()); //Position of the file cursor
    chunk.first[1] = SIZECHUNK; //Size of the chunk
    //  Check if the buffer will overhead the size of the file
    if(inputFileLength - chunk.first[0] < chunk.first[1] && this->inputFile.gcount())
        chunk.first[1] = inputFileLength - chunk.first[0];
    chunk.second = (unsigned char*) malloc(static_cast<size_t>(chunk.first[1]));

    //Read the chunk from the file
    this->inputFile.read(reinterpret_cast<char *>(&chunk.second[0]), chunk.first[1]);

    //Check if no data was read
    if(!this->inputFile.gcount())
        return {};

    return chunk;
}

/**
 * Write the data of the chunk into the output file
 * @param chunk Data chunk to be written
 */
void FileAccessor::writeChunk(pair<int[2], unsigned char*> chunk) {
    //Locking the access for the other threads
    lock_guard<std::mutex> lock(this->mutexWriteFileOperation);

    //Moving the pointer into the start position of the chunk
    this->outputFile.seekp(chunk.first[0]);

    //Write the chunk into the file
    this->outputFile.write(reinterpret_cast<const char *>(&chunk.second[0]), chunk.first[1]);

    //Free the chunk memory
    free(chunk.second);
}

/**
 * Destructor of FileAccessor
 */
FileAccessor::~FileAccessor() {
    this->inputFile.close();
    this->outputFile.close();
}