/**
 * Test methods
 * test.cpp
 * Purpose : Testing logic of the core program
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 28/11/18
 */

#include <gtest/gtest.h>
#include "../src/Common/Functions.h"
#include "../src/FileAccessor/FileAccessor.h"
#include "../src/ThreadManager/ThreadManager.h"
#include "MD5.h"

using namespace Functions;

//How many threads to use for test methods
const int nbThread = 4;

//////////////////////////////////////////////////////////////
TEST(RC4, encryptTextFromShortFile) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/1_input";
    string pathOutput = "../data/2_input";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string md5Input = MD5(getStringFromFile(pathInput)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_NE(md5Input, md5Output);
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
TEST(RC4, decryptTextFromShortFile) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/2_input";
    string pathOutput = "../data/2_output";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string fileToCompare = "../data/1_input";
    string md5Input = MD5(getStringFromFile(fileToCompare)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_EQ(md5Input, md5Output);
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
TEST(RC4, encryptTextFromBigFile) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/3_input";
    string pathOutput = "../data/4_input";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string md5Input = MD5(getStringFromFile(pathInput)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_NE(md5Input, md5Output);
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
TEST(RC4, decryptTextFromBigFile) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/4_input";
    string pathOutput = "../data/4_output";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string fileToCompare = "../data/3_input";
    string md5Input = MD5(getStringFromFile(fileToCompare)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_EQ(md5Input, md5Output);
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
TEST(RC4, encryptBigPictureFile) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/5_input.jpg";
    string pathOutput = "../data/6_input";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string md5Input = MD5(getStringFromFile(pathInput)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_NE(md5Input, md5Output);
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
TEST(RC4, decryptBigPictureFile) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/6_input";
    string pathOutput = "../data/6_output.jpg";

    //RC4 work
    FileAccessor fileAccessor(pathInput, pathOutput);
    ThreadManager tm(&fileAccessor, nbThread, key);
    tm.startWork();

    //Prepare Assert
    string fileToCompare = "../data/5_input.jpg";
    string md5Input = MD5(getStringFromFile(fileToCompare)).hexdigest();
    string md5Output = MD5(getStringFromFile(pathOutput)).hexdigest();

    //Assert
    ASSERT_EQ(md5Input, md5Output);
}