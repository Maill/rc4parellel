#include <iostream>
#include <vector>
#include "RC4.h"
#include <queue>
#include <thread>
#include <mutex>
#include <sstream>
#include <fstream>
#include <map>
#include <future>

using namespace std;

map<int, string> launchWork(int nbThreads, const string &inputFile, const string &key);
void writeIntoFile(map<int, string> parts, const string &outputFile);
bool checkFileExtention(const string &str, const string &suffix);

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

    map<int, string> parts = launchWork(nbThreads, inputFile, key);

    if(method == "-e"){
        if(!checkFileExtention(outputFile, ".rc4")) {
            outputFile += ".rc4";
        }
    }
    else {
        if(!checkFileExtention(outputFile, ".decrypt")) {
            outputFile += ".decrypt";
        }
    }

    writeIntoFile(parts, outputFile);

    return 0;
}

map<int, string> launchWork(int nbThreads, const string &inputFile, const string &key) {
    ifstream t(inputFile);
    string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    map<int, string> parts;

    int h = 0;
    for(int i = 0; i < (int)str.length(); i += (str.length()/nbThreads)) {
        parts[h] = str.substr(static_cast<unsigned long>(i), (str.length() / nbThreads));
        h++;
    }

    deque<thread> threads;
    deque<future<string>> threadFutures;

    int indexesBounds = 0;

    for(int j = 0; j < nbThreads; j++) {
        RC4 rc4;
        rc4.setKey(key, static_cast<int>(key.length()));

        if(j != 0){
            indexesBounds = static_cast<int>(indexesBounds + parts[j-1].length()-1);
            rc4.setIndexes(indexesBounds);
        }

        threadFutures.emplace_front(async(&RC4::encrypt, rc4, parts[j], parts[j].length()));
    }

    for(int k = 0; k < nbThreads; k++) {
        threadFutures[k].wait();
        parts[k] = threadFutures[k].get();
    }

    return parts;
}

void writeIntoFile(map<int, string> parts, const string &outputFile) {
    fstream file(outputFile, fstream::in | fstream::out | fstream::trunc);

    for(int i = 0; i < (int)parts.size(); i++) {
        file << parts[i];
    }

    file.close();
}

bool checkFileExtention(const string &str, const string &suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}