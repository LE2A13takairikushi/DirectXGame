#pragma once
#include "object.h"
#include "ViewProjection.h"

class Enemy : public object
{
public:
	void Initialize(Model* model_, TextureHandle textureHandle_);
	void Update();
	void Draw(ViewProjection viewProjection_);
	void OnCollision();
};

