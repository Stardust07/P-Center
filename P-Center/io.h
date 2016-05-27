#ifndef IO_H
#define IO_H
#include "Input.h"
#include "solution.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
bool readTxtInstance(const string &instancePath, Input &input);
bool writeFile(const Solution &sln);
#endif