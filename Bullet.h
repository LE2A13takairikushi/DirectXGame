#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Utill.h"
#include "ViewProjection.h"

class Bullet
{
public:

	void Initialize();
	void Initialize(Model* model, Vector3 pos);
	void Update();
	void Draw(ViewProjection viewProjection_);

protected:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	TextureHandle textureHandle_;
};

