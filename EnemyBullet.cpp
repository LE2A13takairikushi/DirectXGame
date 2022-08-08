#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, Vector3 pos, Vector3 velocity)
{
	Bullet::Initialize(model, pos);
	velocity_ = velocity;
	deathTimer = 180;
}

void EnemyBullet::Update()
{
	--deathTimer;
	if (deathTimer <= 0)
	{
		isDead = true;
	}

	velocity_.normalize();
	velocity_ *= moveSpd;

	worldTransform_.translation_ += velocity_;
	Bullet::Update();
}

void EnemyBullet::OnCollision()
{
	isDead = true;
}