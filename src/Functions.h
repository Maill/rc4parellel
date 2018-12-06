//
// Created by olivier on 29/11/18.
//

#ifndef RC4PARALLEL_FUNCTIONS_H
#define RC4PARALLEL_FUNCTIONS_H

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

namespace Functions {
    map<int, pair<int, unsigned char*>> launchWork(int nbThreads, const string &inputFile, const string &key);
    void writeIntoFile(map<int, pair<int, unsigned char*>> parts, const string &outputFile, int fileSize);
    bool checkFileExtention(const string &str, const string &suffix);
    string getStringFromFile(string path);

}


#endif //RC4PARALLEL_FUNCTIONS_H
