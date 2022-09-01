#pragma once
#include "Bullet.h"

class EnemyBullet : public Bullet
{
public:
	void Initialize(Model* model, Vector3 pos, Vector3 velocity, TextureHandle tex);
	void Update();

	bool IsDead() const { return isDead; };

	void OnCollision();
private:
	Vector3 velocity_;
	int deathTimer = 0;
	bool isDead = false;

	float moveSpd = 0.5f;

};