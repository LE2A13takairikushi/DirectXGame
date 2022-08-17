#include "ModelManager.h"

ModelManager::ModelManager()
{
	model_ = Model::Create();
	skydome = Model::CreateFromOBJ("skydome");
	firewisp = Model::CreateFromOBJ("firewisp");
	player = Model::CreateFromOBJ("tank_head");
	body = Model::CreateFromOBJ("tank_body");
	taiya = Model::CreateFromOBJ("tank_taiya");
}

ModelManager::~ModelManager()
{
	delete model_;
	delete skydome;
	delete firewisp;
	delete player;
	delete body;
	delete taiya;
}