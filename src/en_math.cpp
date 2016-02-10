#include "../incl/en_math.h"

int forced_into(int into, int put)
{
  int counter = 0;

	while(into > 0)
	{
		into -= put;
		counter++;
	}

	return counter;
}
