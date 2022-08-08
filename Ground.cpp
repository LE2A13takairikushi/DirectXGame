#include "Ground.h"

void Ground::Initialize()
{

}

void Ground::Initialize(Model* model_, TextureHandle textureHandle_)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	this->textureHandle_ = textureHandle_;

	worldTransform_.scale_ = { 100.0f,10.0f,100.0f };
	worldTransform_.translation_ = { 0,-30.0f,0 };
}

void Ground::Update()
{
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
	//Object::Update();
}

void Ground::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
