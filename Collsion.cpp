#include "Collsion.h"
#include "Utill.h"

//なんか見た目より当たり判定が広そうに感じる
//多分スケールを半径として扱っているから？
bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB)
{
	int DistanceX = worldTransformA.translation_.x - worldTransformB.translation_.x;
	int DistanceY = worldTransformA.translation_.y - worldTransformB.translation_.y;
	int DistanceZ = worldTransformA.translation_.z - worldTransformB.translation_.z;

	DistanceX = Abs(DistanceX);
	DistanceY = Abs(DistanceY);
	DistanceZ = Abs(DistanceZ);

	if (DistanceX <= worldTransformA.scale_.x + worldTransformB.scale_.x &&
		DistanceY <= worldTransformA.scale_.y + worldTransformB.scale_.y &&
		DistanceZ <= worldTransformA.scale_.z + worldTransformB.scale_.z)
	{
		return true;
	}
	return false;
}

bool LineFloarCol(Vector3 dVec,Vector3 senbunPos, Vector3 heimenPos,Vector3 normalVec)
{
	//ジャンプの方向ベクトル
	//Vector3 v = line.upVec;
	Vector3 v = dVec;

	//線分上の点
	//Vector3 p1 = line.GetWorldTrans().translation_;
	Vector3 p1 = senbunPos;

	//平面上の点
	Vector3 p0 = heimenPos;

	//平面の法線ベクトル
	Vector3 n = normalVec;

	Vector3 v1 = v - n;

	if (v1.dot(n) == 0 ||v.dot(n) != 0)
	{
		return true;
	}
	return false;
}

bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB)
{
	Vector3 posA = worldTransformA.translation_;
	Vector3 posB = worldTransformB.translation_;

	//スケールのXを横幅として扱っている
	//多分ちゃんと半径を作った方がいい
	float rA = worldTransformA.scale_.x;
	float rB = worldTransformB.scale_.x;

	if ((posB.x - posA.x) * (posB.x - posA.x) +
		(posB.y - posA.y) * (posB.y - posA.y) +
		(posB.z - posA.z) * (posB.z - posA.z) <=
		(rA + rB) * (rA + rB))
	{
		return true;
	}
	return false;
}

bool SphereCol(Vector3 posA, Vector3 posB, float rA, float rB)
{
	if ((posB.x - posA.x) * (posB.x - posA.x) +
		(posB.y - posA.y) * (posB.y - posA.y) +
		(posB.z - posA.z) * (posB.z - posA.z) <=
		(rA + rB) * (rA + rB))
	{
		return true;
	}
	return false;
}