#include "enemyEventManager.h"

void enemyEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_,TextureManager::Load("spawn.png"));
	SetObjects();
}

void enemyEventManager::SetObjects()
{
	CreateEventBox({ 100,160,160 }, {2.0f,2.0f,2.0f});
	CreateEventBox({ -5,190,200 }, { 2.0f,2.0f,2.0f });
	//CreateEventBox({ 0,155,200 }, { 2.0f,2.0f,2.0f });
}