#include "Matrix4.h"
#include <math.h>

Matrix4 Matrix4::RotArbitrary(Vector3 axis, float rad)
{
	//クオータニオンというもの
	axis.normalize();
    float sn = sin(rad / 2);
    axis.x *= sn;
    axis.y *= sn;
    axis.z *= sn;
    float w = cos(rad / 2);
    

	Vector3 X = {
		1 - (2 * (axis.y * axis.y)) - (2 * (axis.z * axis.z)),
		(2 * axis.x * axis.y) + (2 * w * axis.z),
		(2 * axis.x * axis.z) - (2 * w * axis.y),
	};

	Vector3 Y = {
		(2 * axis.x * axis.y) - (2 * w * axis.z),
		1 - (2 * (axis.x * axis.x)) - (2 * (axis.z * axis.z)),
		(2 * axis.y * axis.z) + (2 * w * axis.x),
	};

	Vector3 Z = {
		(2 * axis.x * axis.z) + (2 * w * axis.y),
		(2 * axis.y * axis.z) - (2 * w * axis.x),
		1 - (2 * (axis.x * axis.x)) - (2 * (axis.y * axis.y)),
	};

    return Matrix4(
       X.x, X.y, X.z,0,
	   Y.x, Y.y, Y.z,0,
	   Z.x, Z.y, Z.z,0,
       0, 0, 0, 1
    );
}

Matrix4 Matrix4::MatrixUint()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				m[i][j] = 1;
			}
			else
			{
				m[i][j] = 0;
			}
		}
	}

	return *this;
}

//Matrix4& Matrix4::operator *(const Matrix4 m2)
//{
//	Matrix4 temp;
//
//	for (int i = 0; i < rows; i++)
//	{
//		for (int j = 0; j < m2.cols; j++)
//		{
//			temp.m[i][j] = 0;
//			for (int k = 0; k < m2.rows; k++)
//			{
//				temp.m[i][j] = temp.m[i][j] + (m[i][k] * m2.m[k][j]);
//			}
//		}
//	}
//	return temp;
//}
//
//Matrix4& Matrix4::operator *=(const Matrix4 m2)
//{
//	*this = *this * m2;
//	return *this;
//}