#pragma once

class Vector2
{
public:
	float x; //x成分
	float y; //y成分

public:
	//コンストラクタ
	Vector2();
	Vector2(float x,float y);

	//メンバ関数
	float length() const;
	Vector2& normalize();
	float dot(const Vector2& v) const;		//内積を求める
	float cross(const Vector2& v) const;	//外積を求める

	//単項演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	//代入演算子オーバーロード
	Vector2& operator+= (const Vector2& v);
	Vector2& operator-= (const Vector2& v);
	Vector2& operator*= (float s);
	Vector2& operator/= (float s);
};

//２項演算子オーバーロード
const Vector2& operator+(const Vector2& v1,const Vector2& v2);
const Vector2& operator-(const Vector2& v1,const Vector2& v2);
const Vector2& operator*(const Vector2& v, float s);
const Vector2& operator*(float s, const Vector2& v);
const Vector2& operator/(const Vector2& v, float s);