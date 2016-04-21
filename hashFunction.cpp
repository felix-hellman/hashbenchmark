#include "hashFunction.h"

const unsigned int TABLESIZE = 1770;

unsigned int hashFunction(string word)
{
	int hashValue = word[0];
	for(int i = 0; i < word.size() ;i++)
	{
		hashValue+= word[i];		
		hashValue*=(i + word[i]);
	}	

	return abs(hashValue)%(TABLESIZE+1);
}
