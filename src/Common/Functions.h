/**
 * Generic functions
 * Functions.h
 * Purpose : Generic functions
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 29/11/18
 */

#ifndef RC4PARALLEL_FUNCTIONS_H
#define RC4PARALLEL_FUNCTIONS_H

///Common Includes
#include "../Common/Includes.h"

namespace Functions {
    /**
     * Get the output path string out of path input string
     * @param pathInputFile Path of input file
     * @param method Selected method
     * @return Path output file
     */
    string getPathOutputFile(const string &pathInputFile, const string &method);

    /**
     * Get content string of a file
     * @param path Path of the file
     * @return Content string of file
     */
    string getStringFromFile(string path);
}

#endif //RC4PARALLEL_FUNCTIONS_H
