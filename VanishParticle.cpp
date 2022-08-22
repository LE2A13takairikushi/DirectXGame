#include "VanishParticle.h"

void VanishParticle::Initialize(Vector3 initPos,Vector3 initScale,float scaleSpd,Model* model)
{
	BoxObj::Initialize(model);
	worldTransform_.translation_ = initPos;

	this->scaleSpd = scaleSpd;

	//‰ŠúˆÊ’uŒˆ’è
	//-0.1‚©‚ç0.1‚Ü‚Å‚Ì”ÍˆÍ
	moveVec.x = RNG(-10, 10) * 0.01f;
	moveVec.y = RNG(-10, 10) * 0.01f;
	moveVec.z = RNG(-10, 10) * 0.01f;

	worldTransform_.scale_ = initScale;
}

void VanishParticle::Update()
{
	move = { 0,0,0 };

	--timer;
	//if (timer <= 0)
	if (worldTransform_.scale_.x <= 0)
	{
		isDead = true;
	}

	if (isDead == false)
	{
		move.x += moveVec.x;
		move.y += moveVec.y;
		move.z += moveVec.z;

		if (worldTransform_.scale_.x > 0)
		{
			worldTransform_.scale_.x -= scaleSpd;
			worldTransform_.scale_.y -= scaleSpd;
			worldTransform_.scale_.z -= scaleSpd;
		}
	}

	worldTransform_.translation_ += move;
	MatUpdate();
}

void VanishParticle::Draw(ViewProjection view, TextureHandle tex)
{
	
	model_->Draw(worldTransform_, view, tex);
}
