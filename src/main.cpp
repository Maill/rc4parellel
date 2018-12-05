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

    map<int, string> parts = Functions::launchWork(nbThreads, inputFile, key);

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

    Functions::writeIntoFile(parts, outputFile);

    cout << "Apres : " << Functions::getStringFromFile(outputFile).length() << endl;

    return 0;
}