/**
 * Thread Manager for RC4 work
 * ThreadManager.cpp
 * Purpose : Handle the RC4 workload
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 11/12/18
 */

///Intern include
#include "ThreadManager.h"

/**
 * Constructor of ThreadManager
 * @param fileAccessor Access to input/output file
 * @param numberOfThreads Number of threads to work
 * @param key Encryption RC4 key
 */
ThreadManager::ThreadManager(FileAccessor *fileAccessor, int numberOfThreads, const string& key) {
    this->fileAccessor = fileAccessor;
    this->threadNumber = numberOfThreads;
    this->listThreads = new vector<thread>();
    this->key = key;
}

/**
 * Destructor of ThreadManager
 */
ThreadManager::~ThreadManager() {
    delete this->listThreads;
}

/**
 * Start the RC4 encryption/decryption work
 */
void ThreadManager::startWork() {
    baseRC4 = RC4();
    baseRC4.setKey(key, key.size());

    for(int i = 0; i < threadNumber; i++){
        listThreads->emplace_back(thread(&ThreadManager::threadWork, this));
    }
    waitThreads();
}

/**
 * Method for thread to handle the work
 */
void ThreadManager::threadWork() {
    while (!fileAccessor->noDataToRead()){
        pair<int, vector<unsigned char>> chunk = fileAccessor->getNextChunk();

        if(chunk.second.empty())
            return;

        RC4 rc4;
        rc4 = baseRC4;
        rc4.execute(&chunk);

        fileAccessor->writeChunk(chunk);
    }

}

/**
 * Wait the threads to finish their work
 */
void ThreadManager::waitThreads() {
    for(int i = 0; i < threadNumber; i++){
        listThreads->at(i).join();
    }
}
