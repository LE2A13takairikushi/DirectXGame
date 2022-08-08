#pragma once
#include "Model.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	Model* model_ = nullptr;
	Model* skydome = nullptr;
};