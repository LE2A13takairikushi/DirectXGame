#include "BoxObj.h"

void BoxObj::Initialize(Model* model_,TextureHandle textureHandle_)
{
	LoadModel(model_);
	LoadTexture(textureHandle_);
	worldTransform_.Initialize();

	SetPos({ 50.0f, 20.0f, 0.0f });

	worldTransform_.scale_ = { 10.0f,10.0f,10.0f };

}

void BoxObj::SetPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
}

void BoxObj::Update()
{
	MatUpdate();
}

void BoxObj::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}
