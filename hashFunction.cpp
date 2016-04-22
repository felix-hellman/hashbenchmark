#include "hashFunction.h"


unsigned int hashFunction(string word)
{
	int hashValue = word[0];
	for(int i = 0; i < word.size() ;i++)
	{
		hashValue+= word[i];		
		hashValue*=(i + word[i]);
	}	

	return hashValue;
}
