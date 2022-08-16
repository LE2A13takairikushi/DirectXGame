#include "MyMath.h"
#include <math.h>

float DegreeConversionRad(float frequencymethod)
{
	return PIf / 180 * frequencymethod;
}

float RadConversionDegree(float rad) {
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

float InterpointGetRadian(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1);
}

float InterpointGetRadian(Vector3 vec1, Vector3 vec2)
{
	return atan2(vec2.y - vec1.y, vec2.x - vec1.x);
}

float InterpointGetDegree(float x1, float z1, float x2, float z2)
{
	float radian = atan2(z2 - z1, x2 - x1);
	float degree = RadConversionDegree(radian);
	return degree;
}

float InterpointGetDegree(Vector3 vec1, Vector3 vec2)
{
	float radian = atan2(vec2.z - vec1.z, vec2.x - vec1.x);
	float degree = RadConversionDegree(radian);
	return degree;
}
