#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "Utill.h"
#include "ViewProjection.h"

class Ground
{
public:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	TextureHandle textureHandle_;

	void Initialize();
	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);
};

