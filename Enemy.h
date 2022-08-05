#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "Utill.h"
#include "ViewProjection.h"

class Enemy
{
public:
	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);

private:
	WorldTransform worldTransform;
	Model* model = nullptr;
	TextureHandle textureHandle_;
};

