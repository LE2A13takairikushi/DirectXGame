#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Utill.h"
#include "ViewProjection.h"

class object
{
public:
	WorldTransform GetWorldTrans();
	void LoadModel(Model* model_);
	void LoadTexture(TextureHandle textureHandle_);

	void MatUpdate();

protected:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	TextureHandle textureHandle_;
};

