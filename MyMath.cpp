#include "MyMath.h"
#include "WorldTransform.h"

float FreqConversionRad(float frequencymethod)
{
	return PIf / 180 * frequencymethod;
}

float RadConversionFreq(float rad) {
	return 180 / PIf * rad;
}

float Min(const float& v, const float& low)
{
	if (v < low)return low;
	return v;
}

float Max(const float& v, const float& high)
{
	if (v > high)return high;
	return v;
}