#pragma once
#include "object.h"

class BoxObj : public object
{
public:
	void Initialize(Model* model_, TextureHandle textureHandle);
	void SetPos(Vector3 pos);
	void Update();
	void Draw(ViewProjection viewProjection);
};

