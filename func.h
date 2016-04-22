#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hashFunction.h"

using namespace std;

void inputFromFile(vector<string> &inputVector, const string &filepath);
void hashVectorFill(vector<string> &stringVec, vector<unsigned int> &hashVector, int tablesize);
int hashVectorCollisions(vector<unsigned int> &hashVector,vector<string> &reportVector);
#endif
