#include <iostream>
#include <string>
#include <vector>
#include "func.h"

using namespace std;

int main()
{
	vector<string> inputVector;
	vector<int> hashVector;
	vector<string> reportVector;

	inputFromFile(inputVector);
	hashVector.reserve(inputVector.size());
	hashVectorFill(inputVector,hashVector);
	hashVectorCollisions(hashVector,reportVector);
	for(int i = 0; i < reportVector.size(); i++)
	{
		cout << reportVector[i];
	}
	return 0;
}
