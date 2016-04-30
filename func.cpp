#include "func.h"

void printHelp()
{
	cout << "To use this program edit the hashFunction.cpp file with the function to test" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "To run the hash on a specific input use -f <filepath> " << endl;
	cout << "To run the hash in single table size mode use -s <tablesize> " << endl;
	cout << "To run the hash in intervall table size mode use -i <minTableSize> <maxTableSize>" << endl;
	cout << "If no file is specified then the program will try to open the file \"input\" as default" << endl;  
}
void inputFromFile(vector<string> &stringVec, const string &filepath)
{
	string line;
		
	ifstream myfile(filepath);
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			line.resize(line.length()-1);
			stringVec.push_back(line);
		}
	}
}
void hashVectorFill(const vector<string> &stringVec, vector<unsigned int> &hashVector,int tablesize)
{
	
	while(!hashVector.empty())
		hashVector.pop_back();
	for(auto i = 0; i < stringVec.size(); i++)
		hashVector.push_back(hashFunction(stringVec[i])%tablesize);
}
int hashVectorCollisions(const vector<unsigned int> &hashVector,vector<string> &reportVector)
{
	while(!reportVector.empty())
		reportVector.pop_back();
	auto skip = false;
	auto  max = 0, finalCount = 0, count = 0, maxCount = 0;
	auto min = 0xFFFFFFFF;
	for(auto i = 0; i < hashVector.size(); i++)
	{
		skip = false;
		for(auto x = 0; x < i; x++)
			if(hashVector[i] == hashVector[x])
				skip = true;
		count = 0;
		if(!skip)
		{
			for(auto x = 0; x < hashVector.size(); x++)
			{
				if(hashVector[i] == hashVector[x])
				{
					count++;
				}
			}
			if(count > 1)
				finalCount += count;	
		}
		if(count > maxCount)
			maxCount = count;
		if(hashVector[i] < min)
			min = hashVector[i];
		if(hashVector[i] > max)
			max = hashVector[i];
	}
	stringstream ss;
	ss << "The interval was " << min << " - " <<  max << endl;
	ss << "The total number of collisions was : " << finalCount << endl;
	ss << "There was : " << maxCount << " amount of collisions on one place " << endl;
	reportVector.push_back(ss.str());
	return finalCount;
}
void checkClusters(const vector<unsigned int> &hashVector, string &report)
{
	auto max = 0, x = 0, maxCluster = 1, currentCluster = 1;
	for(auto i = 0; i < hashVector.size(); i++)
		if(hashVector[i] > max)
			max = hashVector[i];
	bool * arr = new bool[max+1]();
	for(auto i = 0; i < max+1; i++)
		arr[i] = false;
	for(auto i = 0; i < hashVector.size(); i++)
	{
		x = hashVector[i];
		while(arr[x] == true)
			x = (x+1)%(max+1);
		arr[x] = true;
	}
	for(auto i = 0; i < max; i++)
	{	
		if(arr[i] && arr[i+1])
		{
			currentCluster++;
		}
		else
		{
			if(currentCluster > maxCluster)
				maxCluster = currentCluster;
			currentCluster = 1;
		}
	}
	delete[] arr;
		
	stringstream ss;
	ss << "The biggest cluster was " << maxCluster << endl;
	report = ss.str();
}
