#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

int hashFunction(string word)
{
	return (int)word[0];
}
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
			stringstream ss;
			ss << "The hash : " << hashVector[i] << " was found " << count << " amount of times " << endl;
			reportVector.push_back(ss.str());
		}
	}
}
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
		cout << reportVector[i] << endl;
	}
	return 0;
}
