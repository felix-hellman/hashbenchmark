#include "func.h"
int swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
void printHelp()
{
	cout << "To use this program edit the hashFunction.cpp file with the function to test" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "To run the hash on a specific input use -f <filepath> " << endl;
	cout << "To run the hash in single table size mode use -s <tablesize> " << endl;
	cout << "To run the hash in intervall table size mode use -i <minTableSize> <maxTableSize>" << endl;
	cout << "If no file is specified then the program will try to open the file \"input\" as default" << endl;  
}
void argumentHandler(int argc, char * argv[], string &filepath, int &minTableSize, int &maxTableSize)
{
	if(argc < 2)
		printHelp();
	else
	{
		for(int i = 0; i < argc; i++)
		{
			if(argv[i] == "-f" && i != argc-1)
				filepath = argv[i+1];
			if(argv[i] == "-i" && i < argc-2);
			{
				minTableSize = stoi(argv[i+1];
				maxTableSize = stoi(argv[i+2];
				if(minTableSize > maxTableSize)
					swap(minTableSize,maxTableSize);
			}
			if(argv[i] == "-s" && i != argc-1)
			{
				minTableSize = stoi(argv[i+1]);
				maxTableSize = minTableSize;
			}		
		}
	}
}
void inputFromFile(vector<string> &stringVec, const string &filepath)
{
	string line;
		
	ifstream myfile(filepath);
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			stringVec.push_back(line);
		}
	}
}
void hashVectorFill(vector<string> &stringVec, vector<unsigned int> &hashVector,int tablesize)
{
	hashVector.clear();
	while(!hashVector.empty())
		hashVector.pop_back();
	for(int i = 0; i < stringVec.size(); i++)
		hashVector.push_back(hashFunction(stringVec[i])%tablesize);
}
int hashVectorCollisions(vector<unsigned int> &hashVector,vector<string> &reportVector)
{
	int count;
	while(!reportVector.empty())
		reportVector.pop_back();
	int finalCount = 0;
	bool skip = false;
	int maxCount = 0;
	for(int i = 0; i < hashVector.size(); i++)
	{
		skip = false;
		for(int x = 0; x < i; x++)
			if(hashVector[i] == hashVector[x])
				skip = true;
		count = 0;
		if(!skip)
		{
			for(int x = 0; x < hashVector.size(); x++)
			{
				if(hashVector[i] == hashVector[x])
				{
					count++;
				}
			}
			if(count > 1)
			{
			//	stringstream ss;
			//	ss << "The hash : \t" << hashVector[i] << "\t :: \t " << count << endl;
			//	reportVector.push_back(ss.str());
				finalCount += count;
			}
		}
		if(count > maxCount)
			maxCount = count;
	}
	stringstream ss;
	ss << "The total number of collisions was : " << finalCount << endl;
	ss << "There was : " << maxCount << " amount of collisions on one place " << endl;
	reportVector.push_back(ss.str());
	return finalCount;
}

