#include "ModelManager.h"

ModelManager::ModelManager()
{
	model_ = Model::Create();
	skydome = Model::CreateFromOBJ("skydome");
}

ModelManager::~ModelManager()
{
	delete model_;
}