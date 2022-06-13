#include "Random.h"
#include <stdlib.h>

int random(int min, int max)
{
	return (rand() % (max + 1 - min) + min);
}