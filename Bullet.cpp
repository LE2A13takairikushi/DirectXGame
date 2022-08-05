#include "Bullet.h"
#include "TextureManager.h"
#include <cassert>

void Bullet::Initialize()
{

}

void Bullet::Initialize(Model* model, Vector3 pos)
{
	assert(model);

	worldTransform_.Initialize();
	model_ = model;
	this->textureHandle_ = TextureManager::Load("bullet.png");

	worldTransform_.translation_ = pos;

	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	
}

void Bullet::Update()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Bullet::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}