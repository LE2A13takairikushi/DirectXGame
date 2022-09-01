#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, Vector3 pos,Vector3 velocity, TextureHandle tex)
{
	Bullet::Initialize(Model::Create(), pos,tex);
	velocity_ = velocity;
	deathTimer = 180;
}

void PlayerBullet::	Update()
{
	--deathTimer;
	if (deathTimer <= 0)
	{
		isDead = true;
	}

	worldTransform_.translation_ += velocity_;
	Bullet::Update();
}

void PlayerBullet::OnCollision()
{
	isDead = true;
}