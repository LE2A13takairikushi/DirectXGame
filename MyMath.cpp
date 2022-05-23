#include "MyMath.h"
#include "WorldTransform.h"

const float XM_PM = 3.14;

float FreqConversionRad(float frequencymethod)
{
	return XM_PM / 180 * frequencymethod;
}

float RadConversionFreq(float rad) {
	return 180 / XM_PM * rad;
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