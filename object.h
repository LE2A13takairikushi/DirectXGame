#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Utill.h"
#include "ViewProjection.h"

class object
{
public:
	WorldTransform GetWorldTrans();

protected:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	TextureHandle textureHandle_;
};

