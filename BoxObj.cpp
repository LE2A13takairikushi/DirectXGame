#include "BoxObj.h"

void BoxObj::Initialize(Model* model_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("hogeta_white.png"));
	worldTransform_.Initialize();
}

void BoxObj::Update()
{
	MatUpdate();
}

void BoxObj::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}

bool BoxObj::GetCheckUpdate()
{
	return isCheckPointUpdate;
}
