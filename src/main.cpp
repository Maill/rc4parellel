/**
 * Entry point of the program
 * main.cpp
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.2
 * @date 11/10/2018
 */

///Common Includes
#include "Common/Includes.h"

///Specific Includes
#include "Common/Functions.h"
#include "FileAccessor/FileAccessor.h"
#include "ThreadManager/ThreadManager.h"

/**
 * Entry point of of the program
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Exit code
 */
int main(int argc, char *argv[]) {

    //Checking arguments
    if(argc != 5){
        cout << "{-e|-d} NB_THREADS KEY INPUT_FILE" << endl;
        return 0;
    }

    //Parsing arguments
    string method = argv[1];
    auto nbThreads = (int)strtol(argv[2], nullptr, 10);
    string key = argv[3];
    string inputFile = argv[4];
    string outputFile;

    //Resolving output file path
    outputFile = Functions::getPathOutputFile(inputFile, method);

    //Configuring RC4 workload
    FileAccessor fileAccessor(inputFile, outputFile);
    ThreadManager tm(&fileAccessor, nbThreads, key);

    //Start RC4 workload
    tm.startWork();

    return 0;
}