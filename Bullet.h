#pragma once
#include "object.h"

class Bullet : public object
{
public:

	void Initialize();
	void Initialize(Model* model, Vector3 pos,TextureHandle tex);
	void Update();
	void Draw(ViewProjection viewProjection_);
};

