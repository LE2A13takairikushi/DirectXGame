#pragma once
class Vector3
{
public:
	float x;	// x成分
	float y;	// y成分
	float z;	// z成分
public:
	Vector3();
	Vector3(float x, float y, float z);

	//メンバ関数
	float length() const;
	Vector3& normalize();
	float dot(const Vector3& v)const;
	Vector3 cross(const Vector3& v)const;

	Vector3 operator+()const;
	Vector3 operator-()const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v1, float s);
const Vector3 operator*(float s, const Vector3& v1);
const Vector3 operator/(const Vector3& v1, float s);

