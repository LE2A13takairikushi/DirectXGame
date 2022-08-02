#pragma once
#include "Vector3.h"
#include "Vector4.h"

/// <summary>
/// 行列
/// </summary>
class Matrix4 {
  public:
	// 行x列
	  //行
	  static const int rows = 4;
	  //列
	  static const int cols = 4;

	  float m[rows][cols];

	// コンストラクタ
	Matrix4();
	// 成分を指定しての生成
	Matrix4(
	  float m00, float m01, float m02, float m03,
	  float m10, float m11, float m12, float m13,
	  float m20, float m21, float m22, float m23,
	  float m30, float m31, float m32, float m33);

	//単位行列にする関数　(注意! : 行列自体を単位行列にするため、
	//これを使う際は専用のインスタンスを作った方がいい)
	Matrix4 MatrixUint();

	Matrix4& operator *=(const Matrix4& m2);

	Matrix4 RotArbitrary(Vector3 axis, float rad);
};
