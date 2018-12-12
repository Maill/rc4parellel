/**
 * System Includes
 * Include.h
 * Purpose : Gather system includes call in one point
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 11/12/2018
 */

#ifndef RC4PARALLEL_INCLUDES_H
#define RC4PARALLEL_INCLUDES_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <sstream>
#include <fstream>
#include <map>
#include <future>
#include <mutex>
#include <vector>
#include <iterator>

using namespace std;

namespace {
    int const SIZECHUNK = 2000;
};

#endif //RC4PARALLEL_INCLUDES_H
