#pragma once
#include "WorldTransform.h"
#include "Vector3.h"
#include "Vector2.h"

bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool BoxCollsion(Vector2 posA, Vector2 posB, Vector2 rA, Vector2 rB);

bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB);

bool SphereCol(Vector3 posA, Vector3 posB, float rA, float rB);

bool LineFloarCol(Vector3 senbunPos1, Vector3 senbunPos2, Vector3 heimenPos, Vector3 normalVec);