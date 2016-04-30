#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "hashFunction.h"

using namespace std;

void printHelp();
bool argumentHandler(int argc, char ** argv, string &filepath, int &minTableSize, int &maxTableSize);
void inputFromFile(vector<string> &inputVector, const string &filepath);
void hashVectorFill(const vector<string> &stringVec,vector<unsigned int> &hashVector, int tablesize);
int hashVectorCollisions(const vector<unsigned int> &hashVector,vector<string> &reportVector);
void checkClusters(const vector<unsigned int> &hashVector, string &report);

#endif
