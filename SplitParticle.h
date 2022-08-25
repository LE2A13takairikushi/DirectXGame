#pragma once
#include "BoxObj.h"

class SplitParticle : public BoxObj
{
public:
	void Initialize(Vector2 moveVecXZ,Vector3 initPos, Vector3 initScale, float scaleSpd, Model* model);
	void Update();
	void Draw(ViewProjection view, TextureHandle tex);

	bool IsDead() { return isDead; };

private:
	Vector3 move = { 0,0,0 };
	Vector3 moveVec = { 0,0,0 };

	float scaleSpd = 0;

	bool isDead = false;
};

