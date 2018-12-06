#include <iostream>
#include "Functions.h"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc != 6){
        cout << "{-e|-d} NB_THREADS INPUT_FILE OUTPUT_FILE KEY" << endl;
        return 0;
    }

    string method = argv[1];
    int nbThreads = atoi(argv[2]);
    string inputFile = argv[3];
    string outputFile = argv[4];
    string key = argv[5];

    map<int, pair<int, unsigned char*>> result;

    if(nbThreads > 1){
        result = Functions::launchWork(nbThreads, inputFile, key);
    } else {
        result = Functions::launchWorkSequential(inputFile, key);
    }



    if(method == "-e"){
        if(!Functions::checkFileExtention(outputFile, ".rc4")) {
            outputFile += ".rc4";
        }
    }
    else {
        if(!Functions::checkFileExtention(outputFile, ".decrypt")) {
            outputFile += ".decrypt";
        }
    }

    Functions::writeIntoFile(result, outputFile, (int)Functions::getStringFromFile(inputFile).length());
    
    return 0;
}