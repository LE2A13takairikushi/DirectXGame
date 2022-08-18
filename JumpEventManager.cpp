#include "JumpEventManager.h"

void JumpEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_);
	SetObjects();
}

void JumpEventManager::SetObjects()
{
	CreateEventBox({20,30,0},{2,2,2});
}