#include "func.h"
void swap(int &a, int &b)
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
bool isNumber(const string &toCheck)
{
	for(unsigned int i = 0; i < toCheck.length(); i++)
		if(toCheck[i] < 0x30 || toCheck[i] > 0x39)
			return false; 
	return true;
}
inline bool exists(const string &name)
{
	ifstream f(name.c_str());
	return f.good();
}
bool contains(const string &word, char ** arr,int size)
{
	for(int i = 0; i < size; i++)
		if(string(arr[i]) == word)
			return true;	
	return false;
}
bool argumentHandler(int argc, char ** argv, string &filepath, int &minTableSize, int &maxTableSize)
{
	if(argc < 2)
		return true;
	else
	{
		for(int i = 1; i < argc; i++)
		{
			if(string(argv[i]) == string("-f"))
			{
				if(i >= argc-1)
					return true;
				filepath = argv[i+1];
				if(!exists(filepath))
					return true;	
			}
			else if(string(argv[i]) == string("-i"))
			{
				if(!isNumber((string(argv[i+1]))) || !isNumber((string(argv[i+2]))) || contains("-s",argv,argc))
					return true;
				minTableSize = stoi(string(argv[i+1]));
				maxTableSize = stoi(string(argv[i+2]));
				if(minTableSize > maxTableSize)
					swap(minTableSize,maxTableSize);
			}
			else if(string(argv[i]) == "-s")
			{
				if(!isNumber(string(argv[i+1])) || contains("-i",argv,argc))
					return true;
				minTableSize = stoi(string(argv[i+1]));
				maxTableSize = minTableSize;
			}		
		}
	}
	return false;
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
	for(unsigned int i = 0; i < stringVec.size(); i++)
		hashVector.push_back(hashFunction(stringVec[i])%tablesize);
}
int hashVectorCollisions(const vector<unsigned int> &hashVector,vector<string> &reportVector)
{
	int count;
	while(!reportVector.empty())
		reportVector.pop_back();
	int finalCount = 0;
	bool skip = false;
	int maxCount = 0;
	unsigned int min = 0xFFFFFFFF;
	unsigned int max = 0;
	for(unsigned int i = 0; i < hashVector.size(); i++)
	{
		skip = false;
		for(unsigned int x = 0; x < i; x++)
			if(hashVector[i] == hashVector[x])
				skip = true;
		count = 0;
		if(!skip)
		{
			for(unsigned int x = 0; x < hashVector.size(); x++)
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
	auto max = 0, x = 0;
	int maxCluster = 1, currentCluster = 1;
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
	for(int i = 0; i < max; i++)
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
