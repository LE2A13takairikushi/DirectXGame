#include "Utill.h"
#include <stdlib.h>

int Abs(int a)
{
	if (a < 0)
	{
		a = -a;
	}
	return a;
}

int RNG(int min, int max, bool preciseMode)
{
	if (!preciseMode) {
		return (rand() % (max + 1 - min) + min);
	}

	int ret = 0;
	do {
		ret = rand();
	} while (ret >= RAND_MAX - RAND_MAX % (max + 1 - min));
	ret = ret % (max + 1 - min) + min;
	return ret;
}