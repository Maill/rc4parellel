/**
 * Generic functions
 * Functions.cpp
 * Purpose : Generic functions
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 29/11/18
 */

///Intern include
#include "Functions.h"

/**
 * Get the output path string out of path input string
 * @param pathInputFile Path of input file
 * @param method Selected method
 * @return Path output file
 */
string Functions::getPathOutputFile(const string &pathInputFile, const string &method){
    if(method == "-e"){
        return pathInputFile + ".rc4";
    }
    else {
        return pathInputFile + ".decrypt";
    }
}

/**
 * Get content string of a file
 * @param path Path of the file
 * @return Content string of file
 */
string Functions::getStringFromFile(string path){
    ifstream t(path, ios::binary);
    string str((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    return str;
}