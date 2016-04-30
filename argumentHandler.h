#ifndef ARGUMENTHANDLER_H
#define ARGUMENTHANDLER_H
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

class ArgumentHandler
{
	private:
	bool isNumber(const string &toCheck) const;
	bool exists(const string &name) const;
	bool contains(const string &word,char ** arr, int size) const;
	unsigned int minTableSize;
	unsigned int maxTableSize;
	string filepath;
	public:
	ArgumentHandler(int argc, char ** argv);
	bool isValid() const; 	
	int generateErrorCode() const; 	
	unsigned int getMinTableSize() const;
	unsigned int getMaxTableSize() const;
	string getFilePath() const;
};
#endif
