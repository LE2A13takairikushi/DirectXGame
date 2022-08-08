#include "Skydome.h"

void Skydome::Initialize(Model* model_)
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
	worldTransform_.scale_ = { 1,1,1 };

	this->model_ = model_;
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
