#pragma once
#include "BoxObj.h"

class Particle : public BoxObj
{
public:
	void Initialize(Vector3 initPos, Model* model);
	void Update();
	void Draw(ViewProjection view, TextureHandle tex);

	bool IsDead() { return isDead; };

private:
	int	timer = 60;

	Vector3 move = {0,0,0};
	Vector3 moveVec = {0,0,0};

	Vector3 initScale = { 0.5f,0.5f,0.5f };

	bool isDead = false;
};

