#pragma once
#include "object.h"
#include "ViewProjection.h"

class Ground : public object
{
public:

	void Initialize();
	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);
};

