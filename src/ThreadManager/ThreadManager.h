/**
 * Thread Manager for RC4 work
 * ThreadManager.h
 * Purpose : Handle the RC4 workload
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 11/12/18.
 */

#ifndef RC4PARALLEL_THREADMANAGER_H
#define RC4PARALLEL_THREADMANAGER_H

///Common includes
#include "../Common/Includes.h"

///Special includes
#include "../FileAccessor/FileAccessor.h"
#include "../RC4/RC4.h"

class ThreadManager {
    public:
        /**
         * Constructor of ThreadManager
         * @param fileAccessor Access to input/output file
         * @param numberOfThreads Number of threads to work
         * @param key Encryption RC4 key
         */
        ThreadManager(FileAccessor* fileAccessor, int numberOfThreads, const string& key);

        /**
         * Destructor of ThreadManager
         */
        ~ThreadManager();

        /**
         * Start the RC4 encryption/decryption work
         */
        void startWork();

    private:
        /**
         * Method for thread to handle the work
         */
        void threadWork();

        /**
         * Wait the threads to finish their work
         */
        void waitThreads();

        /**
         * Handle the access to the input/output file
         */
        FileAccessor* fileAccessor;

        /**
         * Thread that are being use for the operation
         */
        vector<thread>* listThreads;

        /**
         * RC4 encryption key
         */
        string key;

        /**
         * Number of thread to use
         */
        int threadNumber;
};


#endif //RC4PARALLEL_THREADMANAGER_H
