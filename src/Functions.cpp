//
// Created by olivier on 29/11/18.
//

#include "Functions.h"

map<int, string> Functions::launchWork(int nbThreads, const string &inputFile, const string &key) {
    ifstream t(inputFile, ios::binary);
    string str((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    map<int, string> parts;

    cout << "Avant : " << str.length() << endl;

    int h = 0;
    for(int i = 0; i < (int)str.length(); i += (str.length() % 1500)) {
        parts[h] = str.substr(static_cast<unsigned long>(i), (str.length() % 1500));
        h++;
    }

    deque<thread> threads;
    deque<future<string>> threadFutures;

    int indexesBounds = 0;

    for(int j = 0; j < parts.size(); j=j+nbThreads) {

        for(int k = 0; k < nbThreads; k++) {
            if(j+k >= parts.size())
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
            if(j+l >= parts.size())
                break;

            threadFutures[l].wait();
            parts[j+l] = threadFutures[l].get();
        }

        threadFutures.clear();
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