#include "Enemy.h"

void Enemy::Initialize(Model* model_, TextureHandle textureHandle_)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	this->textureHandle_ = textureHandle_;

	worldTransform_.translation_ = { 10,10,0 };
}

void Enemy::Update()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

void Enemy::OnCollision()
{
	
}