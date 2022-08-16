#include "ModelManager.h"

ModelManager::ModelManager()
{
	model_ = Model::Create();
	skydome = Model::CreateFromOBJ("skydome");
	firewisp = Model::CreateFromOBJ("firewisp");
	player = Model::CreateFromOBJ("player");
}

ModelManager::~ModelManager()
{
	delete model_;
	delete skydome;
	delete firewisp;
	delete player;
}