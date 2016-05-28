#ifndef IO2_H
#define IO2_H
#include "Input.h"
#include "solution.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
bool readTxtInstance(const string &instancePath, Input &input);
bool writeFile(const Solution &sln, int time);
#endif