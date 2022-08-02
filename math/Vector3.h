#pragma once
class Vector3
{
public:
	float x;	// x¬•ª
	float y;	// y¬•ª
	float z;	// z¬•ª
public:
	Vector3();
	Vector3(float x, float y, float z);

	//ƒƒ“ƒoŠÖ”
	float length() const;

	//•Ô‚·‚Ì‚Í’·‚³‚Ì“ñæ ‚È‚Ì‚Åg‚¤Û‚É‚Í”äŠr‚·‚é‘ÎÛ‚à2æ‚µ‚Ä”äŠr‚·‚é‚Æ
	//ˆ—‚ğŒyŒ¸‚Å‚«‚é
	float lengthSquared() const;
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

