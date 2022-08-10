#pragma once
#include "WorldTransform.h"
#include "Vector3.h"

bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool SphereCol(Vector3 posA, Vector3 posB, float rA, float rB);

bool LineFloarCol(Vector3 senbunPos1, Vector3 senbunPos2, Vector3 heimenPos, Vector3 normalVec);