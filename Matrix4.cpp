#include "Matrix4.h"

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