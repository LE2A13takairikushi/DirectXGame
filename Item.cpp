#include "Item.h"

void Item::Initialize(Model* model, TextureHandle tex)
{
	object::LoadModel(model);
	object::LoadTexture(tex);
	worldTransform_.Initialize();
}

void Item::Update()
{
	object::MatUpdate();
}

void Item::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view, textureHandle_);
}
