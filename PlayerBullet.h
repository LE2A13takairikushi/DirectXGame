#pragma once
#include "Bullet.h"

class PlayerBullet : public Bullet
{
public:
	void Initialize(Model* model, Vector3 pos, Vector3 velocity);
	void Update();

	bool IsDead() const { return isDead; };

private:
	Vector3 velocity_;
	int deathTimer = 0;
	bool isDead = false;

};

