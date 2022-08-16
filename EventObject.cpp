#include "EventObject.h"

void EventObject::Initialize(Model* model_)
{
	object::LoadModel(model_);
	object::LoadTexture(TextureManager::Load("enemy.png"));
	worldTransform_.Initialize();
}

void EventObject::Update()
{
	object::MatUpdate();
}

void EventObject::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_,view,textureHandle_);
}
