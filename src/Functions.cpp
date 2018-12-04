//
// Created by olivier on 29/11/18.
//

#include "Functions.h"

map<int, string> Functions::launchWork(int nbThreads, const string &inputFile, const string &key) {
    ifstream t(inputFile, ios::binary);
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

void Functions::writeIntoFile(map<int, string> parts, const string &outputFile) {
    ofstream file(outputFile, fstream::in | fstream::out | fstream::trunc | ios::binary);

    for(int i = 0; i < (int)parts.size(); i++) {
        file << parts[i];
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