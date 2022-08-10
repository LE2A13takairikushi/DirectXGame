#include "BoxObj.h"

void BoxObj::Initialize(Model* model_,TextureHandle textureHandle_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("green.png"));
	worldTransform_.Initialize();

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
