#include "BoxObj.h"

void BoxObj::Initialize(Model* model_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("brick.png"));
	worldTransform_.Initialize();
}

void BoxObj::Update()
{
	MatUpdate();
}

void BoxObj::Draw(ViewProjection viewProjection, Vector3 shake)
{
	WorldTransform tempworld = worldTransform_;
	tempworld.translation_ += screenShake;
	tempworld.translation_ += shake;
	tempworld.UpdateMatrix();
	tempworld.TransferMatrix();

	
	model_->Draw(tempworld, viewProjection,textureHandle_);
}

bool BoxObj::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void BoxObj::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}
