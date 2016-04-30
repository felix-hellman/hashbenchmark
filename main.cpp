#include <iostream>
#include <string>
#include <vector>
#include "argumentHandler.h"
#include "func.h"

using namespace std;

int main(int argc, char ** argv)
{
	ArgumentHandler ArgHand(argc,argv);

	if(ArgHand.isValid())
	{
		vector<string> inputVector;
		vector<unsigned int> hashVector;
		vector<string> reportVector;
		vector<string> finalVector;

		

		int tablesize = ArgHand.getMinTableSize();
		unsigned int result = 200000;
		unsigned int min = result;
		string collisionreport = "";
		inputFromFile(inputVector,ArgHand.getFilePath());
		for(int i = ArgHand.getMinTableSize(); i <= ArgHand.getMaxTableSize(); i++)
		{
			result = 0;
			hashVectorFill(inputVector,hashVector,i);
			result = hashVectorCollisions(hashVector,reportVector);
			if(result < min)
			{	
				collisionreport = "";
				checkClusters(hashVector,collisionreport);
				while(!finalVector.empty())
					finalVector.pop_back();
				min = result;
				tablesize = i;
				for(unsigned int i = 0; i < reportVector.size(); i++) 
					finalVector.push_back(reportVector[i]);
			}
		}
		for(unsigned int i = 0; i < reportVector.size(); i++)
		{
			cout << finalVector[i];
		}
		if(ArgHand.getMinTableSize() != ArgHand.getMaxTableSize()) 
			cout << "The best table size for this hash and data was : " << tablesize << endl;
		cout << collisionreport << endl;
	}
	else
	{	
		cout << "Invalid arguments or file" << endl << endl;
		printHelp();
	}
	return 0;
}
