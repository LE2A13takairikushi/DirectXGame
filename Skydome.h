#pragma once
#include "object.h"

class Skydome : public object
{
public:
	void Initialize(Model* model_);
	void Draw(ViewProjection viewProjection);
};

