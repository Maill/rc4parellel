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
    this->outputFile = ofstream(pathOutputFile, fstream::in | fstream::out | fstream::trunc | ios::binary);

    //Init variables
    this->inputFileLength = static_cast<int>(this->inputFile.tellg());

    //Return to the beginning of the input file
    this->inputFile.seekg(0, ios::beg);
}

/**
 * Get the next chunk of data of the input file
 * @return A pair with the position of the pointer on the beginning of the read and a vector that encapsulate the data
 */
pair<int, vector<unsigned char>> FileAccessor::getNextChunk() {
    //Locking the access for the other threads
    lock_guard<std::mutex> lock(this->mutexReadFileOperation);

    //Initialize data
    int chunkSize = SIZECHUNK;
    auto pos = static_cast<int>(this->inputFile.tellg());
    //  Check if the buffer will overhead the size of the file
    if(inputFileLength - pos < chunkSize && this->inputFile.gcount())
        chunkSize = inputFileLength - pos;
    vector<unsigned char> chunk(chunkSize, 0);


    //Read the chunk from the file
    this->inputFile.read(reinterpret_cast<char *>(chunk.data()), chunk.size());

    //Check if no data was read
    if(!this->inputFile.gcount())
        return pair<int, vector<unsigned char>>();

    return pair<int, vector<unsigned char>>(pos, chunk);
}

/**
 * Write the data of the chunk into the output file
 * @param chunk Data chunk to be written
 */
void FileAccessor::writeChunk(pair<int, vector<unsigned char>> chunk) {
    //Locking the access for the other threads
    lock_guard<std::mutex> lock(this->mutexWriteFileOperation);

    //Moving the pointer into the start position of the chunk
    this->outputFile.seekp(chunk.first);

    //Write the chunk into the file
    ostream_iterator<unsigned char> output_iterator(this->outputFile, "");
    copy(chunk.second.begin(), chunk.second.end(), output_iterator);
}

/**
 * Check if there any data left to read in the input file
 * @return
 */
bool FileAccessor::noDataToRead() {
    return inputFile.eof();
}

/**
 * Destructor of FileAccessor
 */
FileAccessor::~FileAccessor() {
    this->inputFile.close();
    this->outputFile.close();
}