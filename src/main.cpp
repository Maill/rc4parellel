#include <iostream>
#include <vector>
#include "RC4.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <sstream>
//#include <omp.h>
#include <cassert>
#include <map>

using std::string;
using std::cout;

// Variables
string encodedString;
int nbThreads;
bool wordFound;
std::map<string, bool> usedword;
std::mutex mutex;

// Déclaration des fonctions
void smasher(std::string const& chars, size_t max_len, std::string const& cur);
void handler_attack(std::string const& chars, int max_len, int threadNumber);
string getCur(int size);
bool UsedWords(bool clear, std::string search);

///////////////////////////////////
int main() {

    wordFound = false;
    nbThreads = 3;

    RC4 rc4;
    std::string key = "nicola";
    std::string text = "justsomeramdomtext";

    //crypt
    rc4.setKey(key, key.length());
    encodedString = rc4.encrypt(text, text.length());
    cout << encodedString << std::endl;

    //decrypt
    rc4.setKey(key, key.length());
    string decodedString = rc4.encrypt(encodedString, encodedString.length());
    cout << decodedString << std::endl;

    //attacking
    std::deque<std::thread> threads;

    //handler_attack("abcdefghijklmnopqrstuvwxyz", 1, 1);
    //smasher("abcdefghijklmnopqrstuvwxyz", 1, "");

    for(int k = 0; k < nbThreads; k++){
        string cur = getCur(k+1);
        size_t size = 4+k+1;

        threads.emplace_front(std::thread(smasher, "abcdefghijklmnopqrstuvwxyz", size, ""));
    }

    /*while(wordFound){
        for(int l = 0; l < nbThreads; l++){
            threads[l].;
        }

    }*/

    for(int l = 0; l < nbThreads; l++){
        threads[l].join();
    }

    return 0;
}

///////////////////////////////////
void smasher(std::string const& chars, size_t max_len, std::string const& cur) {
    if(cur.length() == max_len || wordFound) {
        return;
    }
    else {
        for(auto c : chars) {

            std::string next = cur + c;

            if(!UsedWords(false, next)){
                if(usedword.size() >= 10000000){
                    UsedWords(true, "");
                }

                //usedword[next] = true;

                RC4 rc4;
                rc4.setKey(next, next.length());
                string decodedString = rc4.encrypt(encodedString, encodedString.length());
                //cout << decodedString << " | " << max_len << " | " << next << std::endl;

                if(decodedString == "justsomeramdomtext"){
                    cout << decodedString << std::endl;
                    cout << "key : " << next << std::endl;
                    wordFound = true;
                }
            }

            smasher(chars, max_len, next);
        }
    }
}
///////////////////////////////////
void handler_attack(std::string const& chars, int max_len, int threadNumber){
    cout << "Début du travail du thread numéro : " << threadNumber << std::endl;
    while(!wordFound){
        if(wordFound)
            break;

        cout << "Thread " << threadNumber << " | Taille actuelle du mot : " << max_len << std::endl;

        string cur;

        for(int i = 0; i < max_len - 1; i++){
            cur += 'a';
        }

        smasher(chars, max_len, cur);
        max_len += nbThreads;
    }
}
///////////////////////////////////
bool string_is_valid(const std::string &str)
{
    return find_if(str.begin(), str.end(),
                   [](char c) { return !(isalnum(c) || (c == ' ')); }) == str.end();
}
///////////////////////////////////
string getCur(int size){
    string cur;
    for(int i = 0; i < size - 1; i++){
        cur += 'a';
    }
    return cur;
}
///////////////////////////////////
bool UsedWords(bool clear, std::string search){
    std::lock_guard<std::mutex> lock(mutex);
    if(clear){
        usedword.clear();
        cout << "Cleared table" << std::endl;
    }
    if(search != ""){
        if(usedword[search]){
            return true;
        } else {
            usedword[search] = true;
            cout << "Added : " << search << std::endl;
            return false;
        }
    }
}