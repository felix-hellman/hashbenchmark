#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hashFunction.h"

using namespace std;

void inputFromFile(vector<string> &inputVector);
void hashVectorFill(vector<string> &stringVec, vector<int> &hashVector);
void hashVectorCollisions(vector<int> &hashVector,vector<string> &reportVector);
#endif
