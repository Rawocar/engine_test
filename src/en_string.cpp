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

//------------------------------------------------------------------------
//------------------------------------------------------------------------

bool is_str_in_str(const char * pSrc, const char * pStr)
{
	unsigned int i = 0;
	unsigned int is = 0;
	unsigned int found = 0;
	unsigned int len_str = strlen(pStr);
	bool flag = 0;

	while(pSrc[i] != '\0')
	{
		if(pSrc[i] == pStr[is])
		{
			found++;
			is++;

			if(found == len_str)
			{
				flag = 1;
				break;
			}
		}
		else
		{
			found = 0;
			is = 0;
		}

		i++;
	}

	return flag;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

unsigned int last_position_of_char(const char * pStr, char c)
{
	unsigned int i = 0;
	unsigned int pos = 0;

	while(pStr[i] != '\0')
	{
		if(pStr[i] == c)
			{pos = i;}
		
		i++;
	}

	return pos;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void copy_str_offset(const char * pSrc, char * pBuffer, unsigned int offset)
{
	unsigned int i = 0;
	
	while(pSrc[i] != '\0')
	{
		if(i > offset)
			{break;}

		pBuffer[i] = pSrc[i];
		i++;
	}
}
