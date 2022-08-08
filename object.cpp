#include "object.h"
#include <cassert>

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

void object::MatUpdate()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}
