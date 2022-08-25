#include "SplitParticle.h"

void SplitParticle::Initialize(Vector2 moveVecXZ,Vector3 initPos, Vector3 initScale, float scaleSpd, Model* model)
{
	BoxObj::Initialize(model);
	worldTransform_.translation_ = initPos;

	this->scaleSpd = scaleSpd;

	//‰ŠúˆÊ’uŒˆ’è
	moveVec.x = moveVecXZ.x;
	moveVec.z = moveVecXZ.y;

	worldTransform_.scale_ = initScale;
}

void SplitParticle::Update()
{
	move = { 0,0,0 };

	//--timer;
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

void SplitParticle::Draw(ViewProjection view, TextureHandle tex)
{
	model_->Draw(worldTransform_, view, tex);
}
