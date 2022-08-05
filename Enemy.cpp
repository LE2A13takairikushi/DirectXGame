#include "Enemy.h"

void Enemy::Initialize(Model* model_, TextureHandle textureHandle_)
{
	worldTransform.Initialize();
	model = model_;
	this->textureHandle_ = textureHandle_;

	worldTransform.translation_ = { 10,10,0 };
}

void Enemy::Update()
{
	worldTransform.UpdateMatrix();
	worldTransform.TransferMatrix();
}

void Enemy::Draw(ViewProjection viewProjection_)
{
	model->Draw(worldTransform, viewProjection_, textureHandle_);
}