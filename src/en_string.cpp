#include "../incl/en_string.h"

unsigned int count_in_str(const char * pText, char c)
{
	unsigned int counter = 0;
	unsigned int i = 0;

	while(pText[i] != '\0')
	{
		if(pText[i] == c)
			{counter++;}

		i++;
	}

	return counter;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned int first_appear(const char * pText, char c)
{
  unsigned int i = 0;

	while(pText[i] != '\0' && pText[i] != c)
		{i++;}

	return i;
}
