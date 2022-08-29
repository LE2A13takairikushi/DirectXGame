#include "Item.h"
#include <math.h>

void Item::Initialize(Model* model, TextureHandle tex)
{
	object::LoadModel(model);
	object::LoadTexture(tex);
	worldTransform_.Initialize();
}

void Item::Update()
{
	worldTransform_.rotation_.y += 0.01f;

	object::MatUpdate();
}

void Item::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view, textureHandle_);
}
