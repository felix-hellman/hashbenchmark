#include <iostream>
#include <string>
#include <vector>
#include "func.h"

using namespace std;

int main(int argc, char *argv[])
{
	int minTableSize, maxTableSize;
	if(argc == 2)
	{	
		minTableSize = stoi(argv[1]);
		maxTableSize = minTableSize;
		cout << "Doing single run with table size : " << minTableSize;
	}
	if(argc > 2)
	{
		minTableSize = stoi(argv[1]);
		maxTableSize = stoi(argv[2]);
		cout << "Doing interval run with table size : " << minTableSize << " to " << maxTableSize << endl;
	}
	if(argc < 2)
	{
		cout << "Usage \n./benchmark tablesize " << endl;
		cout << "./benchmark minTableSize maxTableSize" << endl;
	}
	else
	{
		vector<string> inputVector;
		vector<unsigned int> hashVector;
		vector<string> reportVector;
		vector<string> finalVector;

		int tablesize = minTableSize;
		unsigned int result = 200000;
		unsigned int min = result;
		inputFromFile(inputVector);
		for(int i = minTableSize; i <= maxTableSize; i++)
		{
			result = 0;
			hashVectorFill(inputVector,hashVector,i);
			result = hashVectorCollisions(hashVector,reportVector);
			if(result < min)
			{
				while(!finalVector.empty())
					finalVector.pop_back();
				min = result;
				tablesize = i;
				for(int i = 0; i < reportVector.size(); i++) 
					finalVector.push_back(reportVector[i]);
			}
		}
		for(int i = 0; i < reportVector.size(); i++)
		{
			cout << finalVector[i];
		}
		if(argc > 2 ) 
			cout << "The best table size for this hash and data was : " << tablesize << endl;
	}
	return 0;
}
