#include "JumpEventManager.h"

void JumpEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_, TextureManager::Load("jumpBox.png"));
	SetObjects();
}

void JumpEventManager::SetObjects()
{
	CreateEventBox({20,20,80},{2,2,2});
}