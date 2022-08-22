#include "Particle.h"
#include "Utill.h"

void Particle::Initialize(Vector3 initPos,Model* model)
{
	BoxObj::Initialize(model);
	worldTransform_.translation_ = initPos;
	moveVec.x = RNG(-100,100) * 0.01f;
	//moveVec.y = RNG(-1,1);
	moveVec.y = 0.1f;
	moveVec.z = RNG(-100,100) * 0.01f;

	worldTransform_.translation_.x += moveVec.x;
	worldTransform_.translation_.z += moveVec.z;

	worldTransform_.translation_.y += RNG(0, 500) * 0.01f;

	worldTransform_.scale_ = initScale;
}

void Particle::Update()
{
	move = { 0,0,0 };

	--timer;
	if (timer <= 0)
	{
		isDead = true;
	}

	if (isDead == false)
	{
		move.y += moveVec.y;

		if (worldTransform_.scale_.x >= 0)
		{
			worldTransform_.scale_.x -= 0.01f;
			worldTransform_.scale_.y -= 0.01f;
			worldTransform_.scale_.z -= 0.01f;
		}
	}

	worldTransform_.translation_ += move;
	MatUpdate();
}

void Particle::Draw(ViewProjection view, TextureHandle tex)
{
	if (worldTransform_.scale_.x > 0.08f)
	{
		model_->Draw(worldTransform_, view, tex);
	}
}
