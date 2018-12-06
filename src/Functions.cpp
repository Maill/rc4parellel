//
// Created by olivier on 29/11/18.
//

#include "Functions.h"

map<int, pair<int, unsigned char*>> Functions::launchWork(int nbThreads, const string &inputFile, const string &key) {
    ifstream t(inputFile, ios::binary);
    string str((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    map<int, string> parts;
    map<int, pair<int, unsigned char*>> partsToReturn;
    
    int partsIndex = 0;
    int fragmentationCount = 0;
    int paq = 20000;
    if(str.length() > 1000000)
        paq = 400000;

    for(int i = 0; i < (int)str.length() / paq; i++) {
        parts[partsIndex] = str.substr(fragmentationCount, paq);
        partsIndex++;
        fragmentationCount += paq;
    }
    if(str.length() % paq != 0){
        parts[partsIndex] = str.substr(fragmentationCount, (str.length() % paq));
    }

    deque<thread> threads;
    deque<future<pair<int, unsigned char*>>> threadFutures;

    int indexesBounds = 0;

    for(int j = 0; j < (int)parts.size(); j=j+nbThreads) {

        for(int k = 0; k < nbThreads; k++) {
            if(j+k >= (int)parts.size())
                break;

            string part = parts[j+k];

            RC4 rc4;
            rc4.setKey(key, static_cast<int>(key.length()));

            if(j != 0 || j+k > 0){
                indexesBounds = static_cast<int>(indexesBounds + parts[j+k-1].length()-1);
                rc4.setIndexes(indexesBounds);
            }

            threadFutures.emplace_back(async(&RC4::encrypt, rc4, part, part.length()));
        }

        for(int l= 0; l < nbThreads; l++) {
            if(j+l >= (int)parts.size())
                break;

            threadFutures[l].wait();
            partsToReturn[j+l] = threadFutures[l].get();
        }

        threadFutures.clear();
    }

    parts.clear();

    return partsToReturn;
}

map<int, pair<int, unsigned char*>> Functions::launchWorkSequential(const string &inputFile, const string &key) {
    ifstream t(inputFile, ios::binary);
    string str((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    map<int, pair<int, unsigned char*>> partsToReturn;

    RC4 rc4;
    rc4.setKey(key, (int)key.size());
    partsToReturn[0] = rc4.encrypt(str, (int)str.length());

    return partsToReturn;
}


void Functions::writeIntoFile(map<int, pair<int, unsigned char*>> parts, const string &outputFile, int fileSize) {
    ofstream file(outputFile, fstream::in | fstream::out | fstream::trunc | ios::binary);

    for(int i = 0; i < (int)parts.size(); i++) {
        fileSize -= parts[i].first;
        if(fileSize < 0){
            for(int j = 0; j < parts[i].first + fileSize; j++){
                file << parts[i].second[j];
            }
        } else {
            for(int j = 0; j < parts[i].first; j++){
                file << parts[i].second[j];
            }
        }
    }

    file.close();
}

bool Functions::checkFileExtention(const string &str, const string &suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

string Functions::getStringFromFile(string path){
    ifstream t(path, ios::binary);
    string str((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    return str;
}