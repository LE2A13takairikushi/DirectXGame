#include "Skydome.h"

void Skydome::Initialize(Model* model_)
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
	worldTransform_.scale_ = { 10.0f,10.0f,10.0f };

	object::MatUpdate();

	this->model_ = model_;
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}