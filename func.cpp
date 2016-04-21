#include "func.h"

void inputFromFile(vector<string> &stringVec)
{
	string line;
		
	ifstream myfile("input");
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{
			stringVec.push_back(line);
		}
	}

}
void hashVectorFill(vector<string> &stringVec, vector<int> &hashVector)
{
	for(int i = 0; i < stringVec.size(); i++)
		hashVector.push_back(hashFunction(stringVec[i]));
}
void hashVectorCollisions(vector<int> &hashVector,vector<string> &reportVector)
{
	string reportTemplate = "";
	int count;
	int finalCount = 0;
	bool skip = false;
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
				stringstream ss;
				ss << "The hash : \t" << hashVector[i] << "\t :: \t " << count << endl;
				reportVector.push_back(ss.str());
				finalCount += count;
			}
		}
	}
	stringstream ss;
	ss << "The total number of collisions was : " << finalCount << endl;
	reportVector.push_back(ss.str());
}

