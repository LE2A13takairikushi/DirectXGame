#include "JumpEventManager.h"

void JumpEventManager::Initialize(Model* model_)
{
	EventManager::Initialize(model_, TextureManager::Load("jumpBox.png"));
	SetObjects();
}

void JumpEventManager::SetObjects()
{
	//地面に置くくらいに設置すると抜ける危険性がある
	CreateEventBox({20,20,80},{2,2,2});

	CreateEventBox({ 140,155,220 },{2,2,2});

	//CreateEventBox({ 90,155,280 },{2,2,2});
	//CreateEventBox({ 90,180,250 },{2,2,2});
}