#include "enemyEventManager.h"

void enemyEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_);
	SetObjects();
}

void enemyEventManager::SetObjects()
{
	CreateEventBox( { 0, 15, 60 }, {2.0f,2.0f,2.0f});
	CreateEventBox({ 0,150,200 }, { 2.0f,2.0f,2.0f });
}