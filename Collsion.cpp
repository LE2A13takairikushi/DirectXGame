#include "Collsion.h"
#include "Utill.h"

//�Ȃ񂩌����ڂ�蓖���蔻�肪�L�����Ɋ�����
//�����X�P�[���𔼌a�Ƃ��Ĉ����Ă��邩��H
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

bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB)
{
	Vector3 posA = worldTransformA.translation_;
	Vector3 posB = worldTransformB.translation_;

	//�X�P�[����X�������Ƃ��Ĉ����Ă���
	//���������Ɣ��a���������������
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