#pragma once

class Vector2
{
public:
	float x; //x����
	float y; //y����

public:
	//�R���X�g���N�^
	Vector2();
	Vector2(float x,float y);

	//�����o�֐�
	float length() const;
	Vector2& normalize();
	float dot(const Vector2& v) const;		//���ς����߂�
	float cross(const Vector2& v) const;	//�O�ς����߂�

	//�P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector2& operator+= (const Vector2& v);
	Vector2& operator-= (const Vector2& v);
	Vector2& operator*= (float s);
	Vector2& operator/= (float s);
};

//�Q�����Z�q�I�[�o�[���[�h
const Vector2& operator+(const Vector2& v1,const Vector2& v2);
const Vector2& operator-(const Vector2& v1,const Vector2& v2);
const Vector2& operator*(const Vector2& v, float s);
const Vector2& operator*(float s, const Vector2& v);
const Vector2& operator/(const Vector2& v, float s);