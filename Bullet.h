#pragma once
#include "object.h"

class Bullet : public object
{
public:

	void Initialize();
	void Initialize(Model* model, Vector3 pos);
	void Update();
	void Draw(ViewProjection viewProjection_);
};

