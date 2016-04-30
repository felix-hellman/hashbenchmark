#include "argumentHandler.h"

ArgumentHandler::ArgumentHandler(int argc, char ** argv)
{
	this->minTableSize = 0;
	this->maxTableSize = 0;
	this->filepath = "";
	int option = -5;
	if(argc >= 2)
	{	
		for(int i = 0; i < argc; i++)
		{
			if(string(argv[i]) == "-f")
				option = 0;
			else if(string(argv[i]) == "-i")
				option = 1;
			else if(string(argv[i]) == "-s")
				option = 2;
			switch (option)
			{
				case 0:
					if(i+1 < argc)
					{
						if(exists(string(argv[i+1])))
						{
							this->filepath = string(argv[i+1]);
							i++;
						}
					}
				break;
				case 1:
					if(i+2 < argc && !contains("-s",argv,argc))
						if(isNumber(argv[i+1]) && isNumber(argv[i+2]))
						{
							this->minTableSize = stoi(string(argv[i+1]));
							this->maxTableSize = stoi(string(argv[i+2]));
							i+=2;
						}
				break;
				case 2:
					if(i+1 < argc && !contains("-i",argv,argc))
						if(isNumber(argv[i+1]))
						{
							this->minTableSize = stoi(string(argv[i+1]));
							this->maxTableSize = minTableSize;
							i++;
						}
				break;
			}
		}
	}
}
bool ArgumentHandler::isNumber(const string &toCheck) const
{
	for(auto i = 0; i < toCheck.length(); i++)
		if(toCheck[i] < 30 || toCheck[i] > 0x39)
			return false;
	return true;
}
bool ArgumentHandler::exists(const string &name) const
{
	ifstream f(name.c_str());
	return f.good();
}
bool ArgumentHandler::contains(const string &word, char ** arr, int size) const
{
	for(int i = 0; i < size; i++)
		if(string(arr[i]) == word)
			return true;
	return false;
}
bool ArgumentHandler::isValid() const
{
	bool flag = true;

	if(maxTableSize < minTableSize)
		flag = false;
	if(!exists(filepath))
		flag = false;
	return flag;
}
int ArgumentHandler::generateErrorCode() const
{
	int err = 0;
	if(maxTableSize < minTableSize)
		err |= 0b1;
	if(!exists(filepath))
		err |= 0b10;
	return err;
}
unsigned int ArgumentHandler::getMinTableSize() const
{
	return this->minTableSize;
}
unsigned int ArgumentHandler::getMaxTableSize() const
{
	return this->maxTableSize;
}
string ArgumentHandler::getFilePath() const
{
	return this->filepath;
}
