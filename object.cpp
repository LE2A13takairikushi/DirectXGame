#include "object.h"
#include <cassert>

object::object()
{
}

object::~object()
{
	//delete model_;
}

WorldTransform object::GetWorldTrans()
{
	return worldTransform_;
}

void object::LoadModel(Model* model_)
{
	assert(model_);
	this->model_ = model_;
}

void object::LoadTexture(TextureHandle textureHandle_)
{
	this->textureHandle_ = textureHandle_;
}

void object::SetPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	initPos = pos;
}

void object::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	initScale = scale;
}

void object::MatUpdate()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

Vector3 object::screenShake = { 0,0,0 };

void object::ScreenShake(Vector2 shake)
{
	screenShake = { shake.x,shake.y ,0 };
}
