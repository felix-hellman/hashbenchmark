#include <iostream>
#include <string>
#include <vector>
#include "func.h"

using namespace std;

int main(int argc, char *argv[])
{
	int minTableSize, maxTableSize;
	string filepath = "";
	if(argc < 2)
	{
		printHelp();	
	}
	else
	{
		argumentHandler(argc,argv);
		vector<string> inputVector;
		vector<unsigned int> hashVector;
		vector<string> reportVector;
		vector<string> finalVector;

		int tablesize = minTableSize;
		unsigned int result = 200000;
		unsigned int min = result;
		inputFromFile(inputVector,filepath);
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
