#pragma once
#include "WorldTransform.h"
#include "Vector3.h"

bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool SphereCol(Vector3 posA, Vector3 posB, float rA, float rB);