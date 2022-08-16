#pragma once
#include "Vector3.h"

const float PIf = 3.1415926f;

float DegreeConversionRad(float frequencymethod);
float RadConversionDegree(float rad);

float Min(const float& v, const float& low);

float Max(const float& v, const float& high);

float InterpointGetRadian(float x1, float y1, float x2, float y2);

float InterpointGetRadian(Vector3 vec1,Vector3 vec2);

float InterpointGetDegree(float x1, float y1, float x2, float y2);

float InterpointGetDegree(Vector3 vec1, Vector3 vec2);